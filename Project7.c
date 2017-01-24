/*****************************************************************************
 * Author:  Justin Ray                                                       *
 * Student ID: XXXXXXXXXXX                                                   *
 * Login Name: XXXXXXXXXXX                                                   *
 * TA:  XXXXXXXXXXX                                                          *
 * Section: 0502                                                             *
 * Summary:  To create a type of database that will store the information of *
 *           a collection of nomekoPs.  This "database" will have the ability*
 *           to print or search for selected monsters and also a training    *
 *           fight simulator to train and strengthen the collection.         *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* START OF STRUCTURE DEFINITIONS */
typedef struct DateType
{
  char month[4];
  int day, year;
} Date;

typedef struct NomekopType
{
  char name[21];
  int id_number, level;
  Date date_obtained;
  char type[21];
  float height, weight;
  char picture[15][36];
} Nomekop;

typedef struct CollectionType
{
  int num_nomekops;
  Nomekop entire_collection[150];
} Collection;

/* END OF STRUCTURE DEFINITIONS */

/* START OF FUNCTION PROTOTYPES */

void read_input_data ( Collection *collection_ptr );
void read_nomekop ( Collection *collection_ptr, int index );
void read_date_obtained ( Collection *collection_ptr, int index );
void display_menu ( void );
int print_nomekop_above_level ( Collection *collection_ptr, int min_level );
void print_nomekop ( Collection *collection_ptr, int nomekop_number );
int search_collection ( Collection *collection_ptr, char *search_string );
void train_nomekops ( Collection *collection_ptr );
void fight_picture ( Nomekop *nomekop1, Nomekop *nomekop2 );
int win_or_lose ( int level );

/* END OF FUNCTION PROTOTYPES */

/* START OF MAIN */
int main()
{
  Collection nomekop_collection;
  int user_choice, min_level, num_nomekops_above_level, end_of_file_variable;
  Collection *collection_ptr;
  char search_string[ 21 ];

  /* BEGINNING OF STATEMENTS */

  collection_ptr = &nomekop_collection;
  printf( "\n" );
  printf( "Reading in data, please wait .... " );
  read_input_data ( collection_ptr );
  printf( "done.\n" );
  while ( end_of_file_variable != EOF )
    {
      printf( "\n" );
      display_menu ();
      end_of_file_variable = scanf( " %d", &user_choice );
      if ( end_of_file_variable != EOF )
	{
	  if ( user_choice == 1 )
	    {
	      printf( "\n" );
	      printf( "Displaying the entire nomekop collection:\n" );
	      print_nomekop_above_level ( collection_ptr, 1 );
	    }
	  else if ( user_choice == 2 )
	    {
	      printf( "\n" );
	      printf( "Please enter the name to search for:\n" );
	      scanf( " %s", search_string );
	      search_collection ( collection_ptr, search_string );
	    }
	  else if ( user_choice == 3 )
	    {
	      printf( "\n" );
	      printf( "Enter the level to look for:\n" );
	      scanf( " %d", &min_level );
	      printf( "Looking for nomekoPs ...\n" );
	      num_nomekops_above_level = print_nomekop_above_level
		(collection_ptr, min_level );
	      if ( num_nomekops_above_level == 0 )
		{
		  printf( "Search for nomekoPs of level %d ", min_level );
		  printf( "or higher has been unsuccessful.\n" );
		}
	    }
	  else if ( user_choice == 4 )
	    {
	      printf( "\n" );
	      train_nomekops( collection_ptr );
	    }
	  else
	    printf( "Sorry, %d is not a valid choice.  Please try again.\n",
		    user_choice );
	}
    }
  printf( "\n" );
  printf( "Thanks for running the nomekoP training simulator written by" );
  printf( " <Justin Ray>.\n" );
  return 0;

} /* END OF MAIN */
/* END OF MAIN */

/* START OF FUNCTION DEFINITIONS */

/*****************************************************************************
 * Function Name:  read_input_data                                           *
 * Parameters: This function will be passed a pointer pointing to the        *
 *             structure, nomekop_collection.                                *
 * Pre-conditions: This function will be passed valid data.                  *
 * Purpose: Will read in the data from the input file and store it in the    *
 *          array, entire_collection, inside the structure, Collection.      *
 * Return Value: None                                                        *
 *****************************************************************************/

void read_input_data ( Collection *collection_ptr )
{
  int index;

  scanf( " %d", &collection_ptr->num_nomekops );
  for( index = 0; index < collection_ptr->num_nomekops; index++ )
    {
      read_nomekop ( collection_ptr, index );
    } /* Post-condition: index >= collection_ptr->num_nomekops */
} /* END read_input data */

/*****************************************************************************
 * Function Name: read_nomekop                                               *
 * Parameters: This function will be passed a pointer to the structure,      *
 *             nomekop_collection, and an int value, index.                  *
 * Pre-conditions: This function will be passed valid data.                  *
 * Purpose: This function will read in the data from the input file and will *
 *          store it in the proper position inside of the array,             *
 *          entire_collection.                                               *
 * Return Value: None                                                        *
 *****************************************************************************/

void read_nomekop ( Collection *collection_ptr, int index )
{
  int index2;
  char dummy[ 36 ];
  scanf( " nomekoP # %d",
	 &collection_ptr->entire_collection[ index ].id_number );
  read_date_obtained( collection_ptr, index );
  scanf( " Name: " );
  gets( collection_ptr->entire_collection[ index ].name );
  scanf( " Level: %d", &collection_ptr->entire_collection[ index ].level );
  scanf( " Type: " );
  gets( collection_ptr->entire_collection[ index ].type );
  scanf( " Height: %fm", &collection_ptr->entire_collection[ index ].height );
  scanf( " Weight: %fkg Picture:",
	 &collection_ptr->entire_collection[ index ].weight );
  gets( dummy );
  for( index2 = 0; index2 < 15; index2++ )
    {
      gets( collection_ptr->entire_collection[ index ].picture[ index2 ] );
    } /* Post-condition: index2 >= 15 */
} /* end read_nomekop */

/*****************************************************************************
 * Function Name: read_date_obtained                                         *
 * Parameters: This function will be passed a pointer to the structure,      *
 *             nomekop_collection, and an int which represents the current   *
 *             index of the array, entire_collection.                        *
 * Pre-conditions: This function will be passed correct values.              *
 * Purpose: This function will read in a month, day, and year from the input *
 *          file and store it in the date_obtained structure in the array,   *
 *          entire collection.                                               *
 * Return Value: None                                                        *
 *****************************************************************************/

void read_date_obtained ( Collection *collection_ptr, int index )
{
  scanf( " Obtained: %s",
	 collection_ptr->entire_collection[ index ].date_obtained.
	 month );
  scanf( " %d,", &collection_ptr->entire_collection[ index ].date_obtained.
	 day );
  scanf( " %d", &collection_ptr->entire_collection[ index ].
	 date_obtained.year );
} /* end read_date_obtained */

/****************************************************************************
 * Function Name: display_menu                                              *
 * Parameters: None                                                         *
 * Pre-conditions: user_choice != EOF                                       *
 * Purpose: This function will print out the menu that the user will select *
 *          his choice from.                                                *
 * Return Value: None                                                       *
 ****************************************************************************/

void display_menu ( void )
  {
    int index;

    for ( index = 0; index < 46; index++ )
      printf( "-" );
    /* Post-condition: index >= 46 */
    printf( "\n" );
    printf( "Please choose from the following menu:\n" );
    for ( index = 0; index < 46; index++ )
      printf( "-" );
    /* Post-condition: index >= 46 */
    printf( "\n" );
    printf( "  1) Display the entire nomekoP collection\n" );
    printf( "  2) Search for a nomekoP by name\n" );
    printf( "  3) Search for a nomekoP by level\n" );
    printf( "  4) Train 2 nomekoPs\n" );
    for ( index = 0; index < 46; index++ )
      printf( "-" );
    printf( "\n" );
    printf( "Enter choice now (1, 2, 3, or 4)\n" );
    printf( "(press <control>-d to quit):\n" );
  } /* END display_menu */

/****************************************************************************
 * Function Name: print_nomekop_above_level                                 *
 * Parameters: Will be passed a pointer to the structure, nomekop_collection*
 *             and an int which represents the lowest level of nomekop that *
 *             is to be printed.                                            *
 * Pre-conditions: All data passed to the function will be correct.         *
 * Purpose: Will print out all nomekops above a certain level.              *
 * Return Value: Will return an int representing the number of nomekops     *
 *               above the indicated level.                                 *
 ****************************************************************************/

int print_nomekop_above_level ( Collection *collection_ptr, int min_level )
{
  int index, num_nomekops_above_level = 0;
  for ( index = 0; index < collection_ptr->num_nomekops; index++ )
    {
      if ( collection_ptr->entire_collection[ index ].level >= min_level )
	{
	  print_nomekop( collection_ptr, index );
	  num_nomekops_above_level++;
	}
    }
  return num_nomekops_above_level;
} /* END print_nomekop_above_level */

/****************************************************************************
 * Function Name: print_nomekop                                             *
 * Parameters: This function will be passed a pointer to the structure,     *
 *             nomekop_collection, and an int representing the index of the *
 *             array entire_collection which is the structure which holds   *
 *             the data of the nomekop to be printed.                       *
 * Pre-conditions: All values passed to the function will be valid.         *
 * Purpose: This function will print out information about a specified      *
 *          nomekop.                                                        *
 * Return Value: None                                                       *
 ****************************************************************************/

void print_nomekop ( Collection *collection_ptr, int nomekop_number )
{
  printf( "nomekoP # %03d <", collection_ptr->entire_collection
	  [ nomekop_number ].id_number );
  printf( "%s>", collection_ptr->entire_collection[ nomekop_number ].name );
  printf( " obtained on %s %d, %d\n", collection_ptr->entire_collection
	  [ nomekop_number ].date_obtained.month, collection_ptr->
	  entire_collection[ nomekop_number ].date_obtained.day,
	  collection_ptr->entire_collection[ nomekop_number ].date_obtained.
	  year );
  printf( "Level %d height %.1fm weight %.3fkg type {%s}\n", collection_ptr->
	  entire_collection[ nomekop_number ].level, collection_ptr->
	  entire_collection[ nomekop_number ].height, collection_ptr->
	  entire_collection[ nomekop_number ].weight, collection_ptr->
	  entire_collection[ nomekop_number ].type );
  printf( "\n" );
} /* END print_nomekop */

/*****************************************************************************
 * Function Name: search_collection                                          *
 * Parameters: Will be passed a pointer to the Collection, nomekop_collection*
 *             and a pointer to a string which will be searched for in the   *
 *             collection of nomekoPs.                                       *
 * Pre-conditions: All values passed to this function will be valid.         *
 * Purpose: Will search for a specific name of a nomekoP in the array,       *
 *          nomekop_collection, and print out the results.  It will be a     *
 *          case-sensitive search.                                           *
 * Return Value: Will return an int representing the number of nomekoPs found*
 *               that have that specific name.                               *
 *****************************************************************************/

int search_collection ( Collection *collection_ptr, char *search_string )
{
  int index, same_name = 0;
  for ( index = 0; index < collection_ptr->num_nomekops; index++ )
    {
      if ( strcmp ( collection_ptr->entire_collection[ index ].name,
		    search_string ) == 0 )
	{
	  same_name++;
	  printf( "Found the following:\n" );
	  print_nomekop ( collection_ptr, index );
	}
    }
  if ( same_name == 0 )
    printf( "Search for \"%s\" failed.\n", search_string );
  return same_name;
} /* END search_collection */

/*****************************************************************************
 * Function Name: train_nomekops                                             *
 * Parameters: Will be passed a pointer to the Collection, nomekop_collection*
 * Pre-conditions: The passed pointer will be valid.                         *
 * Purpose: This function will run the training simulator part of the program*
 *          and will alter the current levels of the nomekoPs that battle.   *
 * Return Value: None                                                        *
 *****************************************************************************/

void train_nomekops ( Collection *collection_ptr )
{
  char nomekop1[ 21 ], nomekop2[ 21 ];
  Nomekop *nomekop1_ptr, *nomekop2_ptr, *first_nomekop_ptr;
  Nomekop *second_nomekop_ptr;
  int same_name1 = 0, same_name2 = 0, index, index2, nomekop_won = 0;
  int seed_number, win_or_lose1, win_or_lose2, increase_value;

  printf( "Enter the name of the 1st nomekoP:\n" );
  scanf( " %s", nomekop1 );
  printf( "Enter the name of the 2nd nomekoP:\n" );
  scanf( " %s", nomekop2 );
  for ( index = 0; index < collection_ptr->num_nomekops; index++ )
    {
      if ( strcmp ( collection_ptr->entire_collection[ index ].name,
		    nomekop1 ) == 0 )
	{
	  same_name1++;
	  nomekop1_ptr = &collection_ptr->entire_collection[ index ];
	}
    }
  if ( same_name1 == 0 )
    printf( "Search for \"%s\" failed.\n", nomekop1 );
  for ( index = 0; index < collection_ptr->num_nomekops; index++ )
    {
      if ( strcmp ( collection_ptr->entire_collection[ index ].name,
		    nomekop2 ) == 0 )
	{
	  same_name2++;
	  nomekop2_ptr = &collection_ptr->entire_collection[ index ];
	}
    }
  if ( same_name2 == 0 )
    printf( "Search for \"%s\" failed.\n", nomekop2 );
  if ( same_name1 + same_name2 == 2 )
    {
      printf( "Enter the random number generator seed:\n" );
      scanf( " %d", &seed_number );
      srand( seed_number );
      printf( "\n" );
      printf( "Now training, %s vs %s\n", nomekop1, nomekop2 );
      fight_picture ( nomekop1_ptr, nomekop2_ptr );
      if ( nomekop1_ptr->level <= nomekop2_ptr->level )
	{
	  first_nomekop_ptr = nomekop1_ptr;
	  second_nomekop_ptr = nomekop2_ptr;
	}
      else
	{
	  first_nomekop_ptr = nomekop2_ptr;
	  second_nomekop_ptr = nomekop1_ptr;
	}
      for ( index2 = 0; index2 < 10 && nomekop_won == 0; index2++ )
	{
	  win_or_lose1 = win_or_lose ( first_nomekop_ptr->level );
	  win_or_lose2 = win_or_lose ( second_nomekop_ptr->level );
	  if ( win_or_lose1 == win_or_lose2 )
	    {
	      printf( "A tie occurred in round %d (both ", index2 + 1 );
	      if ( win_or_lose1 == 1 )
		printf( "won).\n" );
	      else
		printf( "lost).\n" );
	    }
	  else
	    {
	      nomekop_won++;
	      if ( win_or_lose1 == 1 )
		{
		  printf( "nomekoP #%03d (%s) wins over nomekop #%03d (%s)\n",
			  first_nomekop_ptr->id_number,
			  first_nomekop_ptr->name,
			  second_nomekop_ptr->id_number,
			  second_nomekop_ptr->name );
		  if ( first_nomekop_ptr->level >= second_nomekop_ptr->level )
		    if ( first_nomekop_ptr->level < 100 )
		      first_nomekop_ptr->level++;
		  if ( first_nomekop_ptr->level < second_nomekop_ptr->level )
		    {
		      increase_value = ((( second_nomekop_ptr->level -
					  first_nomekop_ptr->level ) / 2 ) +
					((second_nomekop_ptr->level -
					  first_nomekop_ptr->level ) % 2 ) );
		      if ( increase_value + first_nomekop_ptr->level > 100 )
			first_nomekop_ptr->level = 100;
		      else
			first_nomekop_ptr->level += increase_value;
		      if ( second_nomekop_ptr->level > 2 )
			second_nomekop_ptr->level -= 2;
		      else
			second_nomekop_ptr->level = 1;
		    }
		}
	      else if ( win_or_lose2 == 1 )
		{
		  printf( "nomekoP #%03d (%s) wins over nomekop #%03d (%s)\n",
			  second_nomekop_ptr->id_number,
			  second_nomekop_ptr->name,
			  first_nomekop_ptr->id_number,
			  first_nomekop_ptr->name );
		  if ( second_nomekop_ptr->level >= first_nomekop_ptr->level )
		    if ( second_nomekop_ptr->level < 100 )
		      second_nomekop_ptr->level++;
		  if ( second_nomekop_ptr->level < first_nomekop_ptr->level )
		    {
		      increase_value = ((( first_nomekop_ptr->level -
					   second_nomekop_ptr->level ) / 2 ) +
					(( first_nomekop_ptr->level -
					   second_nomekop_ptr->level ) % 2 ));
		      if ( second_nomekop_ptr->level + increase_value > 100 )
			second_nomekop_ptr->level = 100;
		      else
			second_nomekop_ptr->level += increase_value;
		      if ( first_nomekop_ptr->level > 2 )
			first_nomekop_ptr->level -= 2;
		      else
			first_nomekop_ptr->level = 1;
		    }
		}
	    }
	}
      if ( nomekop_won == 0 )
	{
	  if ( nomekop1_ptr->level > 1 )
	    nomekop1_ptr->level--;
	  if ( nomekop2_ptr->level > 1 )
	    nomekop2_ptr->level--;
	}
    }
} /* END train_nomekops */

/*****************************************************************************
 * Function Name: fight_picture                                              *
 * Parameters: This function will be passed two pointers which point to the  *
 *             Nomekop structures of the two nomekoPs to be printed.         *
 * Pre-conditions: The pointers passed to the function will be valid.        *
 * Purpose: This function will print the pictures of two nomekoPs side by    *
 *          side.                                                            *
 * Return Value: None                                                        *
 *****************************************************************************/

void fight_picture ( Nomekop *nomekop1, Nomekop *nomekop2 )
{
  int index, index2, index3, str_length_nomekop1;
  for ( index = 0; index < 15; index++ )
    {
      str_length_nomekop1 = strlen ( nomekop1->picture[ index ] );
      printf( "%s", nomekop1->picture[ index ] );
      for ( index3 = 0; index3 < 35 - str_length_nomekop1; index3++ )
	printf( " " );
      if ( index == 7 )
	printf( "    vs    " );
      else
	printf( "          " );
      printf( "%s", nomekop2->picture[ index ] );
      printf( "\n" );
    }
} /* END fight_picture */

int win_or_lose ( int level ) {

  if ( level > 100 || level < 1 )
    printf( "Your program should never print this.\n" );

  return (rand() % 100) < level;

}
/* END OF FUNCTION DEFINITIONS */
