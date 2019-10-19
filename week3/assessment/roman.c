#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Max possible valid length is 15 "MMMDCCCLXXXVIII";
#define valid_input_length 15

//DEBUG: Set to 1 to check for errors;
int debug = 0;

//Valid roman numerals
const char ref_roman_numeral[]  = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
//Max time each numeral may appear
const int ref_roman_maxtimes[]  = {4, 1, 4, 1, 4, 1, 3};
//Value of each roman numeral
const int ref_roman_value[] = {1000, 500, 100, 50, 10, 5, 1};
//The above arrays read with the same index values:
//e.g. at [0],
//M(ref_roman_numeral[0])
//can appear a maximum of 3 times(ref_roman_maxtimes[0]) and
//has a value of 1000 (ref_roman_value[0]);

//The sums of the exception cases;
const int ref_exception_sum[] = {900, 400, 90, 40, 9, 4};

int LowertoUpper(char *roman_char);
int isInputValid (char *roman_char);
int isParseSuccessful(int *roman_int, char *roman_char, int s);
int romantoArabic (int *roman_int, int s);

//////////
//This program operates in 5 steps:
//1. Receives roman input in main();
//2. Converts input to uppercase in LowertoUpper();
//3. 1st round of checking for invalid inputs in isInputValid();
//4. Converts input to an int array, and 2nd round of checking in isParseSuccessful();
//5. Calculates arabic output in romantoArabic();
///////// I PUT WAY TOO MUCH WORK INTO THIS. WHY

////////////
int main (int argc, char**argv) {
	if(argc!=2 ){
		printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
	} else {

		char roman_char[strlen(argv[1])];
    strcpy (roman_char, argv[1]);

		//Converts lowercase to uppercase;
		LowertoUpper(roman_char);

		//Check for invalid inputs, e.g. incorrect characters;
    if (!isInputValid(roman_char)) {
      printf("Input is invalid!!\n");
			return 0;
		}

		//Mapping input to an int array for calculation;
    int roman_int[strlen(roman_char)];

    if (!isParseSuccessful(roman_int, roman_char, sizeof(roman_int))) {
      printf("Input is invalid!!\n");
			return 0;
    }

    //Output;
		printf("The roman numeral %s is equal to %d\n", roman_char, romantoArabic(roman_int, sizeof(roman_int)));
	}

	return 0;
}

///////////////
int LowertoUpper (char *roman_char) {

	for (int i=0;i<strlen(roman_char);i++){
		roman_char[i] = toupper(roman_char[i]);
  }

	return 0;
}

////////////
int isInputValid (char *roman_char) {
  //DEBUGGING: Each check comes a debug printf() to help track at what stage the program is at;

	//Check 1: Input length cannot exceed valid_input_length;
  //Uses valid_input_length
	if (strlen(roman_char)>valid_input_length) {
    if (debug) {
	     printf("[DEBUG]Check 1: Maximum Length\n");
    }
		return 0;
	}

	//Check 2: roman_char can only contain characters in ref_roman_numeral;
  //Uses ref_roman_numeral
	for (int i=0;i<strlen(roman_char);i++){
		int chk = 0;

		for (int j=0;j<strlen(ref_roman_numeral); j++) {

			if (roman_char[i] == ref_roman_numeral[j]) {
				chk++;
			}

		}

		if (!chk) {
      if (debug) {
        printf("[DEBUG]Check 2: Invalid Character\n");
      }
      //Ends loop
      i = strlen(roman_char);
			return 0;
		}

	}

	//Check 3: each character can only appear up to 'ref_roman_maxtimes' times;
  //Uses ref_roman_maxtimes
	for (int i=0;i<strlen(ref_roman_numeral);i++){
		int num = 0;

		for (int j=0;j<strlen(roman_char); j++) {

			if (roman_char[j] == ref_roman_numeral[i]) {

        if (num >= ref_roman_maxtimes[i]) {
          if (debug) {
            printf("[DEBUG]Check 3: Too Many Same Characters\n");
          }
          //Ends Loop
          i = strlen(ref_roman_numeral);
          j = strlen(roman_char);
    			return 0;
        } else {
          num++;
        }

			}

    }

	}

  //Check 4: each character can only appear in groups of up to 3;
  //Uses ref_roman_maxtimes
	for (int i=0;i<strlen(roman_char);i++){
		int num = 0;

		for (int j=i;j<(i+3); j++) {

			if (roman_char[j] == roman_char[i]) {
        if (num >= 3) {
          if (debug) {
            printf("[DEBUG]Check 4: Characters cannot exceed groups of 3\n");
          }
          //Ends Loop
          i = strlen(roman_char);
          j = i + 3;
    			return 0;
        } else {
          num++;
        }

			}

    }

	}
  return 1;
}

////////////
int isParseSuccessful (int *roman_int, char *roman_char, int s) {
  //Length of roman_char / roman_int;
  int roman_length = strlen(roman_char);

  //Convert roman_char into roman_int;
  //Uses ref_roman_numeral, ref_roman_value;
  for (int i=0;i<roman_length;i++) {

    for (int j=0;j<strlen(ref_roman_numeral);j++) {

      if (roman_char[i] == ref_roman_numeral[j]) {
        roman_int[i] = ref_roman_value[j];
      }

    }

  }

  //Exception cases: Converts numerals in exception cases into
  //negative values of themselves;
  //i.e. I in IX should be converted from {100} to {-100};
  //Uses ref_exception_sum
  for (int i=0;i<sizeof(ref_exception_sum)/sizeof(ref_exception_sum[0]);i++) {

    for (int j=0;j<roman_length;j++) {

      if (roman_int[j] - roman_int [j-1] == ref_exception_sum[i]) {
        roman_int[j-1] = -(roman_int[j-1]);
      }

    }

  }

  //DEBUG: Print roman_int to check if conversion is correct;
  if (debug) {
    printf("DEBUG: Printing roman_int in isParseSuccessful\n");
    for (int i=0;i<roman_length;i++) {
      printf("%d\n", roman_int[i]);
    }
  }

  //Check 5: Where a NEGATIVE version of a numeral exists, only up to 1 positive version
  //of it can exist;
  //i.e. where "X = -10" exists in roman_int (e.g. in 'XC'), there can only be
  //one instance of 'X = 10',i.e. in XCIX;
  for (int i=0;i<roman_length;i++) {

    if (roman_int[i] < 0) {
      int num = 0;
      for (int j=0;j<roman_length;j++) {

        if (roman_int[j] == -(roman_int[i])) {

          if (!num){
            num++;
          } else {

            if (debug) {
              printf("[DEBUG]Check 5: Too many instances of positive and negative numeral version\n");
            }
            //Ends Loop
            i = roman_length;
            j = i;
            return 0;

          }

        }

      }

    }

  }

  //Check 6: Exception cases should only appear up to ONCE in roman_int;
  //e.g. 'XC' should only appear up to ONCE in roman_int;
  for (int i=0;i<roman_length;i++) {

    //In exception cases, Values 'C', 'X' and 'I' are negative (< 0)
    if (roman_int[i] < 0) {
      int num = 0;

      for (int j=0;j<roman_length;j++) {

        if (roman_int[i] == (roman_int[j])) {

          if (!num) {
            num++;
          } else {
            if (debug) {
              printf("[DEBUG]Check 6: Multiple instances of exception case\n");
            }
            //Ends Loop
            i = roman_length;
            j = i;
            return 0;

          }

        }

      }

    }

  }

  //Check 7: Smaller numerals should not appear before bigger numerals (excl. Exception cases);
  //e.g. I (1) should not appear before M (1000)
  for (int i=0;i<roman_length;i++) {

    for (int j=i;j<roman_length;j++) {

      if (roman_int[j] > roman_int[i] && roman_int[i] > 0) {
        if (debug) {
          printf("[DEBUG]Check 7: Numerals should be in descending order of value\n");
        }
        //Ends Loop
        i = roman_length;
        j = i;
        return 0;
      }

    }

  }

  return 1;
}

////////////
int romantoArabic (int *roman_int, int s) {
  //The final output;
  int arabic = 0;

	for (int j = 0; j<s/sizeof(int);j++) {
		arabic += roman_int[j];
	}

	return arabic;
}

//SAMMYG
