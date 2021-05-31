#include "sha.h"

std::string preprocessing512(std::string mess)
{
  std::stringstream ss;

  // l + 1 + k ≡ 896 mod 1024 (1 -> 1000 0000(bin) = 80(hex) -> 8 bit)
  uint64_t l {8 * (uint32_t)mess.length()};
  uint64_t k {(896 - (8 + l)) % 1024};

  for(size_t i {}; i < mess.length(); ++i)
    ss << std::setw(2) << std::setfill('0') << std::hex << (uint64_t)mess[i];
  ss << "80" << std::setw(32 + k / 4) << std::setfill('0') << std::hex << l;

  return ss.str();
}

std::string hashComputation512(std::string pmess)
{
  uint64_t a,b,c,d,e,f,g,h,t1,t2;
  uint64_t w[80],H[8] {
    0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
    0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179};

  for(size_t i {}, j {}; i < pmess.length(); i += 16, ++j)
  {
    w[j] = std::stoll(pmess.substr(i,16), 0, 16);

    if(j == 15)
    {
      for(j = 16; j < 80; ++j)
        w[j] = s1_512(w[j-2]) + w[j-7] + s0_512(w[j-15]) + w[j-16];
      j = -1;

      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];
      f = H[5];
      g = H[6];
      h = H[7];

      for(size_t t {}; t < 80; ++t)
      {
        t1 = h + S1_512(e) + CH(e,f,g) + K_512[t] + w[t];
        t2 = S0_512(a) + MAJ(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
      }

      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
      H[5] += f;
      H[6] += g;
      H[7] += h;
    }
  }

  std::stringstream ss;
  for(size_t i {}; i < 8; ++i)
    ss << std::setw(8) << std::setfill('0') << std::hex << H[i];

  return ss.str();
}

std::string sha512(std::string mess)
{
  std::string pmess {preprocessing512(mess)};
  return hashComputation512(pmess);
}
