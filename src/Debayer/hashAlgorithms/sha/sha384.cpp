#include "sha.h"

std::string preprocessing384(std::string mess)
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

std::string hashComputation384(std::string pmess)
{
  uint64_t a,b,c,d,e,f,g,h,t1,t2;
  uint64_t w[80],H[8] {
    0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17, 0x152fecd8f70e5939,
    0x67332667ffc00b31, 0x8eb44a8768581511, 0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4};

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
  for(size_t i {}; i < 6; ++i)
    ss << std::setw(8) << std::setfill('0') << std::hex << H[i];

  return ss.str();
}

std::string sha384(std::string mess)
{
  std::string pmess {preprocessing384(mess)};
  return hashComputation384(pmess);
}
