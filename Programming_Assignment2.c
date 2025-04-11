
/*
 Author: Emma Jane Power

 Description: The following program displays an option menu where the user
 is asked to select an option between 1-5 and error checks for any invalid input. 
 Option 1 uses a function which propmts the user to enter a 4 single-digit code 
 where further error checking is carried out to ensure there is no invalid input 
 and displays an appropriate message if an error is detected.
 Option 2 checks to ensure a code has been entered and checks if it is already
 encrypted before passing the user's 4 digit input into a function.
 In this function is where the encryption algorithm takes place,
 the ecryption algorithm:
    swaps the 1st and the 3rd number 
    swaps the 2nd and the 4th number 
    it then incrments each number by 1 
    any number that becomes equal to 10 is changed to 0.
 The encrypted code is then compared to the default code 
 and a message is displayed to the user if their code matches or doesnt match the default.
 Each code entered is only compared to the default code once.
 Option 3 allows the user to decrypt their code by using a decryption algorithem
 which is the following:
    all numbers are subtracted by 1 
    if a number becomes equal to -1 it is reassigned to 9
    the 1st and 3rd number are swapped
    the 2nd and 4th number are swapped
    and a message is displayed to confirm.
 The user is prevented from decrypting code that has not already been previously encrypted.
 Option 4 uses a function to print the amount of times the user was successful and incorrect.
 Option 5 gracefully ends the program.

*/
 
 
#include <stdio.h>

#define SIZE 4
#define ELEMENT0 0
#define ELEMENT1 1
#define ELEMENT2 2
#define ELEMENT3 3

// functions
void enter_code(int*); //option 1 
void encryption (int*, int*, int*, int*, int*); // option 2
void decryption(int*); // option 3
void success_incorrect(int* , int*); // option 4
void end(int*); // option 5

int main() 
{
  // declaring variables
  int access_code[SIZE] = {4,5,2,3};
  int option;
  int i;
  int user_code[SIZE]; 
  int code_entered = 0;
  int encrypted = 0;
  int attempts = 0;
  int successful;
  int incorrect;
  int loop = 0;
  int ret;

  /*
   Do While loop to display the option menu at the beginning
   and after each option is executed 
   the program will exit the loop when the variable 'loop' is incremented 
   whick occurs in option 5 - exit program
  */
  do  
  {
    // displaying option menu 
    printf("\nOPTIONS MENU\n\n");
    printf("1 - enter code\n");
    printf("2 - encrypt code and verify if correct\n");
    printf("3 - decrypt\n");
    printf("4 - success, incorrect\n");
    printf("5 - exit program\n\n");
    
    // asking user to input chosen option 
  	printf("please enter what number option you would like\n");

    // assigning user input into the variable 'option'
    scanf("%d", &option);
    
    //error checking for character input 
    while (getchar() != '\n')
    {
      // displaying message of an invaled input if a character has been entered
      printf("\ninvalid input please enter a single digit\n");
    }

    /*
     switch statement  
     selects which case to go to 
     dependent on the variable 'option'
    */
    switch (option)
    {

      case(1): // option 1 - enter code
      {
        /* 
         calling function enter_code
         passing an array by referance
        */
        enter_code(user_code ); 
        
        /*
         incrementing code_entered to allow for encryption to happen.
         ensure's a code has been entered before encryption
        */
        code_entered++; 

        // setting encrypted to 0 as a new code has been entered 
        if (encrypted > 0)
        {
          encrypted = 0;
        }

        /*
         setting the variable 'attempts' back to 0 
         to allow for new code that is entered 
         to be counted as a successful or incorrect attemp
        */
        if (attempts != 0)
        {
          attempts = 0;
        }
        
        break;
        
      }//end case 1 - enter code

      case(2): //option 2 - ecrypt code and verify if correct
      {
        /*
         if statement used to ensure a code has been entered 
         and not already encrypted before entering the 
         encryption function
        */
        if ( code_entered >= 1 && encrypted == 0)
        {
          /*
           encryption function
           encrypts code
           passing listed arrays and variables by reference 
          */
          encryption ( user_code, access_code, &successful, &incorrect, &attempts);
          
          /*
           stops the encryption of none decrypted code. 
           allows for decryption in option 3 as the code has now been encrypted
          */
          encrypted++;
          

        }// end if

        
        // else if for when code is already encrypted 
        else if ( code_entered >= 1)
        {

          printf("\nyour code has already been encrypted \n"
          "and your successful or incorrect attempt has already"
          " been counted for this code\n"
          "please select another option\n");

        }// end else if

        else // else statement to display to user of an error
        {

          printf("\nyou have not yet entered a code in. Select option 1 if you wish to do so\n");

        }// end else
      
        break;

      }// end case 2 - encryption
      
      case(3): //option 3 - decrypt 
      {
        /*
         if statement ensuring encryption to the code has happend
         before entering the decryption function
        */
        if (encrypted == 1 )
        {
          /*
           decryption function
           decrypts an encrypted code
           pasing an array by reference 
          */
          decryption(user_code);

          /*
           decreasing encrypted variable to ensure
           decryption doesnt happen again before encryption 
          */
          encrypted--;

        }

        else // else statement to display to the user of an error
        {
          printf("\nYour code has not yet been encrypted "
          "or has already been decrypted\n"
          "please select option 2 if you wish to ecrypt\n"
          "or option 1 if you wish to enter in a code\n");
        }
        
        break;

      }// end case 3 - decrypt

      case(4): //option 4 - ecryption successful and incorrect 
      {

        /*
         success_incorrect function
         to display the amount of times a user entered a correct and incorrect code.
         passing two variables by referance
        */
        success_incorrect(&successful , &incorrect);

        break;

      }// end case 4 - successful, incorrect 

      case(5): // 5 - program end 
      {
        /*
         calling the end function.
         function will end the program.  
         passing the variable loop by referance  
        */
        end(&loop);

        break;

      }// end case 5 - program end 

      default: // incase of any invalid user input
      {

        printf("\nInvalid option please select an option\n");

        break;

      }// end default

    }// end switch

  }// end do
  while(loop == 0); // condition of Do While loop

  return 0;

}// end main

/*
 this function prompts the user to input a 4-single digit code
 it is then stored in a 1D array called code_user which has been passed from main,
 while appropriate error checking is carried out
*/
void enter_code(int *code_user)
{
  //declaring function variables 
  int i;
  int ret;

  /*
   Do While loop used for error checking. 
   if any errors are detected the value of 'ret' changes 
   casuing the loop to restart. 
   if no errors are detected then ret keeps its value  
   and the program exits the loop at the end 
  */
  do 
  {
    ret = 1;

    printf("\nPlease enter a 4 digit code\n"); // prompting user for input

    for (i = 0; i < SIZE; i++)
    {
      // entering the users input into ech element of the array 
      scanf("%d", & *(code_user + i) );

      // error checking for invalid input
      // if statement checking if each input is a single positive digit
      if (*(code_user + i) < 0 || *(code_user + i) >= 10)
      {
        // message to show user their input was invalid 
        printf("\ninvalid input enter single digit\n");

        ret--;  

        i = SIZE; //increasing the value of i to jump out of the for loop

      }// end if
    
    }// end for

    // error checking for invalid input
    // clear the input buffer 
    while (getchar() != '\n')
    {
      // shows message that the input is invalid 
      printf("\ninvalid input please enter a single digit\n");

      ret--; // re-assigning value of ret
    }// end while

  }//end do
  while(ret == 0); // Do While condition

}// end enter_code function

/*
 function encryption uses an encryption algorithem to encrypt the users input.
 Afer encryption the function displays to the user if their input 
 does or does not matches the set default access code 
*/
void encryption ( int *code_encrypt ,int *access, int *correct, int *incorrect, int *attempt)
{
  // declaring function variables 
  int temp;
  int i;
  int counter = 0;
  
  /*
   swapping the 1st and 3rd number
   swapping the 2nd and 4th number
   using a temporary variable
  */
  temp = *(code_encrypt + ELEMENT0);
  *(code_encrypt + ELEMENT0) = *(code_encrypt + ELEMENT2);
  *(code_encrypt + ELEMENT2) = temp;
  temp = *(code_encrypt + ELEMENT1);
  *(code_encrypt + ELEMENT1) = *(code_encrypt + ELEMENT3);
  *(code_encrypt + ELEMENT3) = temp;
  
  for (i = 0; i < SIZE; i++)
  {

    // increment each element by 1
    (*(code_encrypt + i))++;

    // if number becomes equal to 10 it's value is changed to 0
    if (*(code_encrypt + i) == 10)
    {
      *(code_encrypt + i) = 0;

    }// end if 
    
  }// end for loop
  
  /*
   if the statement is true the users attempt is marked as corrent or incorrect.
   It allows for the user to encrypt, decrypt and encrypt the same peice 
   of code over and over again without the same code being marked as 
   correct or incorrect.
  */
  if((*attempt) == 0)
  {
    
    for(i = 0; i < SIZE; i++)
    {

      // checking if the encrypted code matches the access code 
      if (*(access + i)  == *(code_encrypt + i) )
      {
        counter++; // using a counter variable to track amount of element matches 

      }// end if

    }// end for 

    /*
     if the counter is the same as the amount of element 
     the encrypted code matches the access code
    */
    if (counter == SIZE)
    {
    
      printf("\nCorrect Code entered \n");

      (*correct)++; // incrementing counter for each correct attempt 

    }// end if

    else // if the encrypted code does not match the access code
    {
      printf("\nWrong Code entered\n");

      (*incorrect)++; // incrementing counter for each incorrect attempt 

    }// end else

    /*
     increasing the attepmt counter to prevent the counting of the same peice of code
     this is re-set when a new code is entered.
    */
    (*attempt)++; 

  }// end if
  
  // printing a statment to let the user know their attemtps as already been counted
  else 
  {

    printf("\nCode encrypted\nThis code has already been counted"
    " as a successful or incorrect attempt\n");

  }// end else

}// end encryption function

/*
 decryption function decrypts a previously encrypted code 
 using a decryption algorithem
*/
void decryption ( int *code_decrypt)
{
  // declaring function variables 
  int i;
  int temp;

  // decryption algorithem

  for ( i = 0; i < SIZE; i++)
  {

    // decreasing all numbers by 1
   (*(code_decrypt + i) )--;

    // numbers that become equal to -1 have their value changed to 9
    if ( *(code_decrypt + i)  == -1)
    {

      *(code_decrypt + i)  = 9;

    } // end if

  }// end for

  /*
   swapping the 1st number with the 3rd number 
   swapping the 2nd number with the 4th number 
   using a temporary variable
  */
  
 temp = *(code_decrypt + ELEMENT0) ;
 *(code_decrypt + ELEMENT0) = *(code_decrypt + ELEMENT2);
 *(code_decrypt + ELEMENT2) = temp;
 temp = *(code_decrypt + ELEMENT1);
 *(code_decrypt + ELEMENT1) = *(code_decrypt + ELEMENT3);
 *(code_decrypt + ELEMENT3) = temp; 
 
 printf("\nCode decrypted\n");// telling the user their code has been decrypted

}// end decryption function

/*
 the following function displays to the user the amount of times 
 their encrypted code matched the default access code both successfully
 and incorrectly
*/
void success_incorrect(int *correct , int *unsuccessful)
{
  // display success and incorrect attempts 
  printf("\nsuccessful attempts = %d\n", *correct); 
  printf("incorrect attempts = %d\n", *unsuccessful);

}// end success_incorrect function

/*
 the function 'end' , gracefully ends the program  
 it increases a variable 
 that will cause the program to jump out of 
 the Do While loop in main
*/
void end(int *turn)
{
  printf("\nProgram end"); // letting the user know the program has ended 

  (*turn)++;
  
} // end of 'end' function