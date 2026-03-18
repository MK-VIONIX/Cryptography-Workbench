#include <bits/stdc++.h>
using namespace std;


string base64_decode(string s){
    string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> val(256, -1);
    for(int i = 0; i < 64; i++) val[table[i]] = i;

    string decoded;
    int buffer = 0, bits = 0;
    for(char c : s){
        if(c == '=') break;
        buffer = (buffer << 6) + val[c];
        bits += 6;
        if(bits >= 8){
            bits -= 8;
            decoded.push_back((buffer >> bits) & 0xFF);
        }
    }
    return decoded;
}

extern "C" {
#include <stdint.h>
}

static const uint8_t sbox[256] = {

  0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
  0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
  0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
  0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
  0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
  0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
  0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
  0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
  0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
  0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
  0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
  0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
  0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
  0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
  0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
  0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};


static const uint8_t Rcon[11] = { 
  0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36
};


static void KeyExpansion(const uint8_t key[16], uint8_t roundKey[176]){
    memcpy(roundKey, key, 16);
    int bytesGenerated = 16;
    int rconIdx = 1;
    uint8_t temp[4];

    while(bytesGenerated < 176){
        for(int i=0; i<4; i++)
            temp[i] = roundKey[bytesGenerated - 4 + i];

        if(bytesGenerated % 16 == 0){
            uint8_t t = temp[0];
            temp[0] = sbox[temp[1]] ^ Rcon[rconIdx];
            temp[1] = sbox[temp[2]];
            temp[2] = sbox[temp[3]];
            temp[3] = sbox[t];
            rconIdx++;
        }
        for(int i=0; i<4; i++){
            roundKey[bytesGenerated] = roundKey[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}


static void AddRoundKey(uint8_t state[16], const uint8_t* roundKey){
    for(int i=0; i<16; i++)
        state[i] ^= roundKey[i];
}
static void InvSubBytes(uint8_t state[16]){
    // generate inverse S‑box on the fly
    for(int i=0; i<16; i++){
        // brute‑force find inverse
        for(int j=0; j<256; j++){
            if(sbox[j] == state[i]){
                state[i] = (uint8_t)j;
                break;
            }
        }
    }
}


static void InvShiftRows(uint8_t state[16]){
    uint8_t tmp[16];
    memcpy(tmp, state, 16);
    // row 1
    state[1] = tmp[13]; state[5] = tmp[1];
    state[9] = tmp[5]; state[13] = tmp[9];
    // row 2
    state[2] = tmp[10]; state[6] = tmp[14];
    state[10] = tmp[2]; state[14] = tmp[6];
    // row 3
    state[3] = tmp[7]; state[7] = tmp[11];
    state[11] = tmp[15]; state[15] = tmp[3];
}


static uint8_t gmul(uint8_t a, uint8_t b){
    uint8_t p = 0;
    for(int i=0; i<8; i++){
        if(b & 1) p ^= a;
        uint8_t hi_bit = (a & 0x80);
        a <<= 1;
        if(hi_bit) a ^= 0x1B;
        b >>= 1;
    }
    return p;
}


static void InvMixColumns(uint8_t state[16]){
    for(int i=0; i<4; i++){
        int idx = i*4;
        uint8_t a = state[idx], b = state[idx+1],
                c = state[idx+2], d = state[idx+3];
        state[idx]   = gmul(a,0x0e) ^ gmul(b,0x0b) ^ gmul(c,0x0d) ^ gmul(d,0x09);
        state[idx+1] = gmul(a,0x09) ^ gmul(b,0x0e) ^ gmul(c,0x0b) ^ gmul(d,0x0d);
        state[idx+2] = gmul(a,0x0d) ^ gmul(b,0x09) ^ gmul(c,0x0e) ^ gmul(d,0x0b);
        state[idx+3] = gmul(a,0x0b) ^ gmul(b,0x0d) ^ gmul(c,0x09) ^ gmul(d,0x0e);
    }
}


void AES128_ECB_decrypt(const uint8_t in[16], const uint8_t key[16], uint8_t out[16]){
    uint8_t state[16];
    memcpy(state, in, 16);

    uint8_t roundKey[176];
    KeyExpansion(key, roundKey);

    AddRoundKey(state, roundKey + 160);

    for(int round = 9; round >= 0; round--){
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKey + round*16);
        if(round){
            InvMixColumns(state);
        }
    }

    memcpy(out, state, 16);
}
string aes_ecb_decrypt(string ciphertext, vector<unsigned char> key){
    string plaintext;
    for(size_t i = 0; i < ciphertext.size(); i += 16){
        uint8_t out[16];
        AES128_ECB_decrypt((const uint8_t*)&ciphertext[i], key.data(), out);
        plaintext.append((char*)out, 16);
    }

    
    if(!plaintext.empty()){
        unsigned char pad = plaintext.back();
        if(pad > 0 && pad <= 16){
            bool ok = true;
            for(size_t i = plaintext.size()-pad; i < plaintext.size(); i++){
                if((unsigned char)plaintext[i] != pad) ok = false;
            }
            if(ok) plaintext.resize(plaintext.size()-pad);
        }
    }

    return plaintext;
}

int main() {
    freopen("challenge_7.txt","r",stdin);
    string text, line;
    while(getline(cin,line)) text+=line;

    string ciphertext = base64_decode(text);
    vector<unsigned char> key={'Y','E','L','L','O','W',' ','S','U','B','M','A','R','I','N','E'};

    string decrypted = aes_ecb_decrypt(ciphertext, key);
    cout << decrypted << endl;
    return 0;
}