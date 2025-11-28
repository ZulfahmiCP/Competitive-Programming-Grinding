#include <bits/stdc++.h>
#define ll long long
using namespace std;

bool dalam_persegi(ll x1, ll y1, ll px1, ll py1, ll px2, ll py2) {
  ll skor = 0;
  if (x1 >= px1 && x1 <= px2) {
    skor++;
  }
  if (y1 >= py1 && y1 <= py2) {
    skor++;
  }
  return skor == 2;
}

bool dalam_lingkaran(ll x, ll y, ll lx, ll ly, ll r) {
  ll jarak = (x-lx)*(x-lx) + (y-ly)*(y-ly);
  return jarak <= r*r;
}

int main() {
  ll t;
  cin >> t;
  vector<ll> l1, l2, l3, p1, p2, p3, p4;
  for (ll i = 0; i < t; i++) {
    char x;
    cin >> x;
    if (x == 'L') {
      ll a, b, c;
      cin >> a >> b >> c;
      l1.push_back(a);
      l2.push_back(b);
      l3.push_back(c);
    } else {
      ll a, b, c, d;
      cin >> a >> b >> c >> d;
      p1.push_back(a);
      p2.push_back(b);
      p3.push_back(c);
      p4.push_back(d);
    }
  }
  ll jumlah_p = p1.size();
  ll jumlah_l = l1.size();
  // Kondisi 1
  bool benar1 = true;
  for (ll i = 0; i < jumlah_l; i++) {
    for (ll j = 0; j < jumlah_p; j++) {
      if (!dalam_persegi(l1[i] + l3[i], l2[i] + l3[i], p1[j], p2[j], p3[j], p4[j])) {
        benar1 = false;
        break;
      }
      if (!dalam_persegi(l1[i] + l3[i], l2[i] - l3[i], p1[j], p2[j], p3[j], p4[j])) {
        benar1 = false;
        break;
      }
      if (!dalam_persegi(l1[i] - l3[i], l2[i] + l3[i], p1[j], p2[j], p3[j], p4[j])) {
        benar1 = false;
        break;
      }
      if (!dalam_persegi(l1[i] - l3[i], l2[i] - l3[i], p1[j], p2[j], p3[j], p4[j])) {
        benar1 = false;
        break;
      }
    }
  }
  if (benar1) {
    cout <<  "SEMUA LINGKARAN DI DALAM PERSEGI PANJANG\n";
    return 0;
  }

  // Kondisi 2
  bool benar2 = true;
  for (ll i = 0; i < jumlah_p; i++) {
    for (ll j = 0; j < jumlah_l; j++) {
      if (!dalam_lingkaran(p1[i], p2[i], l1[j], l2[j], l3[j])) {
        benar2 = false;
        break;
      }
      if (!dalam_lingkaran(p1[i], p4[i], l1[j], l2[j], l3[j])) {
        benar2 = false;
        break;
      }
      if (!dalam_lingkaran(p3[i], p2[i], l1[j], l2[j], l3[j])) {
        benar2 = false;
        break;
      }
      if (!dalam_lingkaran(p3[i], p4[i], l1[j], l2[j], l3[j])) {
        benar2 = false;
        break;
      }
    }
  }
  if (benar2) {
    cout << "SEMUA PERSEGI PANJANG DI DALAM LINGKARAN\n";
    return 0;
  }
  cout << "TIDAK ADA YANG SEPENUHNYA DI DALAM\n";
}