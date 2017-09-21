#include <stdio.h>

int g_sbox[8][4][16] = {
  {
    { 14  ,4  ,13  ,1  ,2  ,15  ,11  ,8  ,3  ,10  ,6  ,12  ,5  ,9  ,0  ,7 },
    { 0  ,15  ,7  ,4  ,14  ,2  ,13  ,1  ,10  ,6  ,12  ,11  ,9  ,5  ,3  ,8 },
    { 4  ,1  ,14  ,8  ,13  ,6  ,2  ,11  ,15  ,12  ,9  ,7  ,3  ,10  ,5  ,0 },
    { 15  ,12  ,8  ,2  ,4  ,9  ,1  ,7  ,5  ,11  ,3  ,14  ,10  ,0  ,6  ,13 }
  },
  {
    { 15  ,1  ,8  ,14  ,6  ,11  ,3  ,4  ,9  ,7  ,2  ,13  ,12  ,0  ,5  ,10 },
    { 3  ,13  ,4  ,7  ,15  ,2  ,8  ,14  ,12  ,0  ,1  ,10  ,6  ,9  ,11  ,5 },
    { 0  ,14  ,7  ,11  ,10  ,4  ,13  ,1  ,5  ,8  ,12  ,6  ,9  ,3  ,2  ,15 },
    { 13  ,8  ,10  ,1  ,3  ,15  ,4  ,2  ,11  ,6  ,7  ,12  ,0  ,5  ,14  ,9 }
  },
  {
    { 10  ,0  ,9  ,14  ,6  ,3  ,15  ,5  ,1  ,13  ,12  ,7  ,11  ,4  ,2  ,8 },
    { 13  ,7  ,0  ,9  ,3  ,4  ,6  ,10  ,2  ,8  ,5  ,14  ,12  ,11  ,15  ,1 },
    { 13  ,6  ,4  ,9  ,8  ,15  ,3  ,0  ,11  ,1  ,2  ,12  ,5  ,10  ,14  ,7 },
    { 1  ,10  ,13  ,0  ,6  ,9  ,8  ,7  ,4  ,15  ,14  ,3  ,11  ,5  ,2  ,12 }
  },
  {
    { 7  ,13  ,14  ,3  ,0  ,6  ,9  ,10  ,1  ,2  ,8  ,5  ,11  ,12  ,4  ,15 },
    { 13  ,8  ,11  ,5  ,6  ,15  ,0  ,3  ,4  ,7  ,2  ,12  ,1  ,10  ,14  ,9 },
    { 10  ,6  ,9  ,0  ,12  ,11  ,7  ,13  ,15  ,1  ,3  ,14  ,5  ,2  ,8  ,4 },
    { 3  ,15  ,0  ,6  ,10  ,1  ,13  ,8  ,9  ,4  ,5  ,11  ,12  ,7  ,2  ,14 }
  },
  {
    { 2  ,12  ,4  ,1  ,7  ,10  ,11  ,6  ,8  ,5  ,3  ,15  ,13  ,0  ,14  ,9 },
    { 14  ,11  ,2  ,12  ,4  ,7  ,13  ,1  ,5  ,0  ,15  ,10  ,3  ,9  ,8  ,6 },
    { 4  ,2  ,1  ,11  ,10  ,13  ,7  ,8  ,15  ,9  ,12  ,5  ,6  ,3  ,0  ,14 },
    { 11  ,8  ,12  ,7  ,1  ,14  ,2  ,13  ,6  ,15  ,0  ,9  ,10  ,4  ,5  ,3 }
  },
  {
    { 12  ,1  ,10  ,15  ,9  ,2  ,6  ,8  ,0  ,13  ,3  ,4  ,14  ,7  ,5  ,11 },
    { 10  ,15  ,4  ,2  ,7  ,12  ,9  ,5  ,6  ,1  ,13  ,14  ,0  ,11  ,3  ,8 },
    { 9  ,14  ,15  ,5  ,2  ,8  ,12  ,3  ,7  ,0  ,4  ,10  ,1  ,13  ,11  ,6 },
    { 4  ,3  ,2  ,12  ,9  ,5  ,15  ,10  ,11  ,14  ,1  ,7  ,6  ,0  ,8  ,13 }
  },
  {
    { 4  ,11  ,2  ,14  ,15  ,0  ,8  ,13  ,3  ,12  ,9  ,7  ,5  ,10  ,6  ,1 },
    { 13  ,0  ,11  ,7  ,4  ,9  ,1  ,10  ,14  ,3  ,5  ,12  ,2  ,15  ,8  ,6 },
    { 1  ,4  ,11  ,13  ,12  ,3  ,7  ,14  ,10  ,15  ,6  ,8  ,0  ,5  ,9  ,2 },
    { 6  ,11  ,13  ,8  ,1  ,4  ,10  ,7  ,9  ,5  ,0  ,15  ,14  ,2  ,3  ,12 }
  },
  {
    { 13  ,2  ,8  ,4  ,6  ,15  ,11  ,1  ,10  ,9  ,3  ,14  ,5  ,0  ,12  ,7 },
    { 1  ,15  ,13  ,8  ,10  ,3  ,7  ,4  ,12  ,5  ,6  ,11  ,0  ,14  ,9  ,2 },
    { 7  ,11  ,4  ,1  ,9  ,12  ,14  ,2  ,0  ,6  ,10  ,13  ,15  ,3  ,5  ,8 },
    { 2  ,1  ,14  ,7  ,4  ,10  ,8  ,13  ,15  ,12  ,9  ,0  ,3  ,5  ,6  ,11 }
  }
};

int sbox(int box, int input) {
  // input bit is 6-bit
  // row: 0xxxx0, col: y0000y
  int row = (((input >> 5) & 0x01) << 1) + (input & 0x01);
  int col = ((input >> 1) & 0x0F);
  return g_sbox[box][row][col];
};

int main(int argc, char *argv[]) {
  int xdt[8][64][16] = {0,};
  FILE *fout = fopen("output.txt", "w");

  printf("Generating XDT...\n");
  // Generate XDT
  for (int input_1 = 0; input_1 < 64; input_1++) {
    for (int input_2 = 0; input_2 < 64; input_2++) {
      int in_xor = input_1 ^ input_2;
      for (int box = 0; box < 8; box++) {
        int output_1 = sbox(box, input_1);
        int output_2 = sbox(box, input_2);
        int out_xor = output_1 ^ output_2;
        xdt[box][in_xor][out_xor]++;
      }
    }
  }

  printf("XDT generated. Writing to file...\n");
  // Write XDT to file
  for (int box = 0; box < 8; box++) {
    fprintf(fout, "S%d-box XDT\n", box+1);  // Write label
    // Write line
    fprintf(fout, "-------");
    for (int i = 0; i < 16; i++) {
      fprintf(fout, "---");
    }
    fprintf(fout, "\n");
    // Write legendary
    fprintf(fout, "|Input|");
    for (int i = 0; i < 18; i++) {
      fprintf(fout, " ");
    }
    fprintf(fout, "Output XOR");
    for (int i = 0; i < 19; i++) {
      fprintf(fout, " ");
    }
    fprintf(fout, "|\n");
    fprintf(fout, "| XOR |");
    for (int out_xor = 0; out_xor < 16; out_xor++) {
      fprintf(fout, "%Xx|", out_xor);
    }
    fprintf(fout, "\n");

    // Write XDT
    for (int in_xor = 0; in_xor < 64; in_xor++) {
      fprintf(fout, "|%4Xx|", in_xor);
      for (int out_xor = 0; out_xor < 16; out_xor++) {
        fprintf(fout, "%2d|", xdt[box][in_xor][out_xor]);
      }
      fprintf(fout, "\n");
    }

    // Write line
    fprintf(fout, "-------");
    for (int i = 0; i < 16; i++) {
      fprintf(fout, "---");
    }
    fprintf(fout, "\n\n");
  }

  // Find best iterative characteristics
  printf("Finding best iterative characteristics...\n");
  double max_prob = 0.0;  // Best iterative characteristic
  unsigned long INPUT_MAX = 0xFFFFFFFF;  // Maximum input value
  // B = 0 case should be ignored, so start from 1
  for (unsigned long B = 1; B <= INPUT_MAX; B++) {
    if (!(B & 0xFFFFF)) {
      printf("Processing B = %08lX\n", B);
    }
    int sbox_input[8] = {0, };
    for (int i = 0; i < 7; i++) {
      sbox_input[i] = (B >> (27-4*i)) & 0x3F;
    }
    sbox_input[0] += ((B & 0x01) << 5);
    sbox_input[7] = ((B << 1) & 0x3F) + ((B >> 31) & 0x01);

    double curr = 1.0;
    for (int box = 0; box < 8; box++) {
      curr *= ((double)xdt[box][sbox_input[box]][0] / 64);
    }

    if (max_prob < curr) {
      max_prob = curr;
      printf("Maximum updated. B: %08lX, ", B);
      fprintf(fout, "Maximum updated. B: %08lX, ", B);
      printf("Probability: %f\n", max_prob);
      fprintf(fout, "Probability: %f\n", max_prob);
    }
  }
  fprintf(fout, "\n");
  fprintf(fout, "Best iterative characteristic: %f\n", max_prob);
  fprintf(fout, "1/234 = %f\n", (float)1/234);

  fclose(fout);
}

