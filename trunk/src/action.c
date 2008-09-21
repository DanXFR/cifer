/*
    Cifer: Automating classical cipher cracking in C
    Copyright (C) 2008  Daniel Richman & Simrun Basuita

    Cifer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cifer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cifer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdinc.h"
void action_do()
{
  int i;
  int frequency_graph[26], identity_frequency_graph[26];
  digram *digrams;
  trigram *trigrams;

  printf("Doing requested action(s)...\n");
 
  if (arg_input) /* Have we got any input files? */
  {
    i = input_open(arg_input);
    if (i != 0)
    {
      printf("input_open failed, returned %i; exiting\n", i);
      exit(1);
    }
  }
 
  /*if () */ /* Will the dictionary be needed? Currenlty only for arg_key */
  /*{
   *  load_dict();
   *}   */

  /* Let's start with the easy stuff */
  
  if (arg_pct) /* Print char -> number table */
  {
    printf("Char -> number table requested... printing...\n");
    print_char_table();
  }
  
  if (arg_gcd) /* Do a GCD calculation */
  {
    printf("GCD of %i and %i: %i\n", arg_gcd_1, arg_gcd_2, 
                              gcd(arg_gcd_1, arg_gcd_2) );
  }

  if (arg_mmi) /* Do a ModMulInv Calcuation */
  {
    if (arg_mmi_1 <= 0 || arg_mmi_2 <= 0 || arg_mmi_1 > arg_mmi_2)
    {
      printf("MMI: Bad Arguments.\n");
    }
    else
    {
      i = gcd(arg_mmi_1, arg_mmi_2);
      if (i != 1) printf("MMI: Simplied args by gcd of %i...\n", i);

      printf("MMI of %i (mod %i): %i\n", arg_mmi_1/i, arg_mmi_2/i,
                modular_multiplicative_inverse(arg_mmi_1/i, arg_mmi_2/i));
    }
  }

  if (arg_freq) /* Do (and print) letter frequency count */
  {
    printf("Letter frequency count requested... doing...\n");
    count_freq(intext, intext_size, frequency_graph);
    create_identity_frequency_graph(identity_frequency_graph, intext_size);
    print_freq(frequency_graph, identity_frequency_graph);
  }
  
  if (arg_pd) /* Print digram counts */
  {
    arg_pd_1 = max(min(arg_pd_1, 26 * 26), 1); /* Enforce minimum and maximum */
    digrams = malloc( sizeof(digram) * arg_pd_1 );

    printf("Printing top %i digram counts\n", arg_pd_1);
    if (digrams == NULL)
    {
      printf("Digrams Malloc fail.\n");
    }
    else
    {
      count_digrams(intext, intext_size, digrams, arg_pd_1);
      print_digrams(digrams, arg_pd_1);

      free(digrams);
    }
  }

  if (arg_pt) /* Print trigram counts */
  {
    arg_pt_1 = max(min(arg_pt_1, 26 * 26 * 26), 1);
    trigrams = malloc( sizeof(trigram) * arg_pt_1 );

    printf("Printing top %i trigram counts\n", arg_pt_1);
    if (trigrams == NULL)
    {  
      printf("Trigrams Malloc fail.\n");
    }
    else
    {
      count_trigrams(intext, intext_size, trigrams, arg_pt_1);
      print_trigrams(trigrams, arg_pt_1);

      free(trigrams);
    }
  }

  /* Ciphers */
  
  if (arg_vig) /* Crack vigenere */
  {
    printf("Vigenere cipher crack requested... doing...\n");
    crack_vigenere(intext, intext_size);
  }

  if (arg_aff) /* Crack Affine */
  {
    printf("Affine cipher crack requested... doing... \n");
    crack_affine(intext, intext_size);
  }

  if (arg_key) /* Decode Keyword */
  {
    printf("Keyword cipher decode mode requested... doing... \n");
    keyword_decode(intext, intext_size, 
                        arg_key_string, strlen(arg_key_string));
  }

  printf("Finished doing requested actions.\n");
}
