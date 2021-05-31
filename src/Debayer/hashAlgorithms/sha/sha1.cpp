#include "sha.h"

std::function<uint32_t(uint32_t,uint32_t,uint32_t)> getFunc(size_t t)
{
  if(t < 20)
    return [](uint32_t x, uint32_t y, uint32_t z) -> uint32_t { return CH(x,y,z); };
  else if(t < 40)
    return [](uint32_t x, uint32_t y, uint32_t z) -> uint32_t { return PARITY(x,y,z); };
  else if(t < 60)
    return [](uint32_t x, uint32_t y, uint32_t z) -> uint32_t { return MAJ(x,y,z); };
  else /* t < 80 */
    return [](uint32_t x, uint32_t y, uint32_t z) -> uint32_t { return PARITY(x,y,z); };

}

std::string preprocessing1(std::string mess)
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

std::string hashComputation1(std::string pmess)
{
  uint32_t a,b,c,d,e,t0;
  uint32_t w[80],H[5] {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};

  for(size_t i {}, j {}; i < pmess.length(); i += 8, ++j)
  {
    w[j] = std::stoll(pmess.substr(i,8), 0, 16);

    if(j == 15)
    {
      for(j = 16; j < 80; ++j)
        w[j] = ROTL_32((w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16]),1);
      j = -1;

      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];

      for(size_t t {}; t < 80; ++t)
      {
        auto f = getFunc(t);
        t0 = ROTL_32(a,5) + f(b,c,d) + e + K[t] + w[t];
        e = d;
        d = c;
        c = ROTL_32(b,30);
        b = a;
        a = t0;
      }

      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
    }
  }

  std::stringstream ss;
  for(size_t i {}; i < 5; ++i)
    ss << std::setw(8) << std::setfill('0') << std::hex << H[i];

  return ss.str();
}

std::string sha1(std::string mess)
{
  std::string pmess {preprocessing1(mess)};
  return hashComputation1(pmess);
}
