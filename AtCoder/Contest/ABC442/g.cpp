WITH periods AS (
    SELECT 
    sm_tuple.1 AS semester_key,
    sm_tuple.2 AS cutoff_date,
    1 AS join_key
    FROM system.one
    ARRAY JOIN [
    ('2015/2016 Ganjil', toDate('2015-08-24')),
    ('2015/2016 Genap', toDate('2016-02-01')),
    ('2016/2017 Ganjil', toDate('2016-08-22')),
    ('2016/2017 Genap', toDate('2017-01-23')),
    ('2017/2018 Ganjil', toDate('2017-08-20')),
    ('2017/2018 Genap', toDate('2018-01-29')),
    ('2018/2019 Ganjil', toDate('2018-08-20')),
    ('2018/2019 Genap', toDate('2019-01-28')),
    ('2019/2020 Ganjil', toDate('2019-08-19')),
    ('2019/2020 Genap', toDate('2020-02-03')),
    ('2020/2021 Ganjil', toDate('2020-08-18')),
    ('2020/2021 Genap', toDate('2021-02-15')),
    ('2021/2022 Ganjil', toDate('2021-08-16')),
    ('2021/2022 Genap', toDate('2022-02-15')),
    ('2022/2023 Ganjil', toDate('2022-08-22')),
    ('2022/2023 Genap', toDate('2023-02-20')),
    ('2023/2024 Ganjil', toDate('2023-08-21')),
    ('2023/2024 Genap', toDate('2024-02-19')),
    ('2024/2025 Ganjil', toDate('2024-08-21')),
    ('2024/2025 Genap', toDate('2025-02-17')),
    ('2025/2026 Ganjil', toDate('2025-08-18')),
    ('2025/2026 Genap', toDate('2026-02-18'))
    ] AS sm_tuple
)

SELECT
    out.semester                                  AS semester,
    out.fakultas                                  AS fakultas,
    out.prodi                                     AS prodi,
    out.prodi_jenjang                             AS prodi_jenjang,
    out.cutoff_date                               AS cutoff_date,
    
    countIf(out.kode_eff = 'C')                    AS cuti,
    countIf(out.kode_eff = 'A')                    AS aktif,
    countIf(out.kode_eff = 'P')                    AS pengunduran_diri_dari_mata_kuliah,
    countIf(out.kode_eff = 'S')                    AS skorsing
FROM
(
    SELECT
        p.semester_key AS semester,
        p.cutoff_date,
        mf.fakultas,
        mf.prodi,
        mf.prodi_jenjang,
        coalesce(
            argMaxIf(h.ncode, h.tanggal_dokumen, h.tanggal_dokumen <= p.cutoff_date),
            mf.ncode_m
        ) AS kode_eff
    FROM periods p
    LEFT JOIN
    (
        SELECT
            m.id AS id_mhs,
            f.nama_resmi    AS fakultas,
            p.nama_resmi    AS prodi,
            j.nama          AS prodi_jenjang,
            toInt32OrNull(m.angkatan) AS angkatan_int,
            1 AS join_key,
            multiIf(
                upper(trim(m.kode_status)) IN ('A','AKTIF'), 'A',
                upper(trim(m.kode_status)) IN ('C','CUTI'),  'C',
                upper(trim(m.kode_status)) IN (
                    'P','PENGUNDURAN','PENGUNDURAN DIRI','PENGUNDURAN DIRI DARI MATA KULIAH'
                ), 'P',
                upper(trim(m.kode_status)) IN ('S','SKORS','SKORSING'), 'S',
                NULL
            ) AS ncode_m
        FROM neosia_dwh.mahasiswa m
        INNER JOIN neosia_dwh.prodi           p ON p.id = m.id_prodi
        INNER JOIN neosia_dwh.fakultas        f ON f.id = p.id_fakultas
        INNER JOIN neosia_dwh.prodi_jenjang   j ON j.id = p.id_prodi_jenjang
    ) AS mf ON p.join_key = mf.join_key
    LEFT JOIN
    (
        SELECT
            rsm.id_mahasiswa    AS id_mhs,
            rsm.tanggal_dokumen AS tanggal_dokumen,
            coalesce(
                (CASE WHEN upper(trim(sm.kode)) IN ('A','C','P','S') THEN upper(trim(sm.kode)) ELSE NULL END),
                (CASE
                    WHEN positionCaseInsensitive(sm.deskripsi, 'aktif')  > 0 THEN 'A'
                    WHEN positionCaseInsensitive(sm.deskripsi, 'cuti')   > 0 THEN 'C'
                    WHEN positionCaseInsensitive(sm.deskripsi, 'skors')  > 0 THEN 'S'
                    WHEN positionCaseInsensitive(sm.deskripsi, 'undur')  > 0 THEN 'P'
                    WHEN positionCaseInsensitive(sm.deskripsi, 'pengunduran') > 0 THEN 'P'
                    ELSE NULL
                END)
            ) AS ncode
        FROM neosia_dwh.riwayat_status_mahasiswa rsm
        INNER JOIN neosia_dwh.status_mahasiswa sm
            ON sm.id = rsm.id_status_mahasiswa
    ) AS h
        ON h.id_mhs = mf.id_mhs
    WHERE isNull(mf.angkatan_int) OR toInt32(substring(p.semester_key, 1, 4)) >= mf.angkatan_int
    GROUP BY
        p.semester_key, p.cutoff_date, mf.fakultas, mf.prodi, mf.prodi_jenjang, mf.id_mhs, mf.ncode_m
) AS out
GROUP BY
    out.semester, out.fakultas, out.prodi, out.prodi_jenjang, out.cutoff_date
ORDER BY
    out.cutoff_date DESC, out.fakultas, out.prodi, out.prodi_jenjang;