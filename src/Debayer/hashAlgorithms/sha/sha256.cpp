#include "sha.h"

std::string preprocessing256(std::string mess)
{
  std::stringstream ss;

  // l + 1 + k ≡ 448 mod 512 (1 -> 1000 0000(bin) = 80(hex) -> 8 bit)
  uint32_t l {8 * (uint32_t)mess.length()};
  uint32_t k {(448 - (8 + l)) % 512};

  for(size_t i {}; i < mess.length(); ++i)
    ss << std::setw(2) << std::setfill('0') << std::hex << (uint32_t)mess[i];
  ss << "80" << std::setw(16 + k / 4) << std::setfill('0') << std::hex << l;

  return ss.str();
}

std::string hashComputation256(std::string pmess)
{
  uint32_t a,b,c,d,e,f,g,h,t1,t2;
  uint32_t w[64],H[8] {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  for(size_t i {}, j {}; i < pmess.length(); i += 8, ++j)
  {
    w[j] = std::stoll(pmess.substr(i,8), 0, 16);

    if(j == 15)
    {
      for(j = 16; j < 64; ++j)
        w[j] = s1_256(w[j-2]) + w[j-7] + s0_256(w[j-15]) + w[j-16];
      j = -1;

      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];
      f = H[5];
      g = H[6];
      h = H[7];

      for(size_t t {}; t < 64; ++t)
      {
        t1 = h + S1_256(e) + CH(e,f,g) + K_256[t] + w[t];
        t2 = S0_256(a) + MAJ(a,b,c);
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

std::string sha256(std::string mess)
{
  std::string pmess {preprocessing256(mess)};
  return hashComputation256(pmess);
}
