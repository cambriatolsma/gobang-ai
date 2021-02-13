#include "gobang.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int compute_move_value()
{
  int value = 0; 
  
  /*
	if (check_win(CPLAYER))
	{
		value += 10000000;
	}

	if (check_win(CPLAYER))
	{
		value -= 10000000;
	}
 */

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] == CPLAYER)
			{
				value += BOARD_VALUES[i][j]; 

				//horizontal

				if (j != 0)
				{
					if (j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == 0)
						{
							value = value + 1000000 + BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
						}
              
						///capped 4 right
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == HPLAYER)
						{
							value = value + 100050 + BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
						}

						///capped 4 left
						if (BOARD[i][j - 1] == HPLAYER && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == 0)
						{
							value = value + 100050 - BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
						}
					}

          if (j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == 0)
						{
							value = value + 100000 + BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3];
							cout << "Open 3" << endl;
						}
              
            ///capped 3 right
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == HPLAYER)
						{
							value = value + 10000 + BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3];
						}

						///capped 3 left
						if (BOARD[i][j - 1] == HPLAYER && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == 0)
						{
							value = value + 10000 - BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3];
						}
					}
				}
        
        if (j + 5 < BOARD_SIZE)
        {
          if(BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == CPLAYER)
          {
            value += 10000000;
          }
        }

				if (j + 4 < BOARD_SIZE)
				{
          ///capped 4 (wall left)
          if (j == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == 0)
          {
            value = value + 100050 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i][j + 1] == 0 && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == CPLAYER)
					{
						value = value + 100050 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
					}

					if ((BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == 0 && BOARD[i][j + 3] == CPLAYER && BOARD[i][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
					}

					if ((BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == 0 && BOARD[i][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
					}
				}

				if (j + 3 < BOARD_SIZE)
				{
          ///capped 4 (wall right)
          if (j + 4 == BOARD_SIZE && BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER)
          {
            value = value + 100050 + BOARD_VALUES[i][j - 1] + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
          }
          
					///gapped 3
					if (BOARD[i][j + 1] == 0 && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3];
					}

					if (BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == 0 && BOARD[i][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i][j + 1] + BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3];
					}
				}

				//vertical

				if (i != 0)
				{
					if (i + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == 0)
						{
							value = value + 1000000 + BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
						}
              
						///capped 4 down
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == HPLAYER)
						{
							value = value + 100050 + BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
						}

						///capped 4 up
						if (BOARD[i - 1][j] == HPLAYER && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == 0)
						{
							value = value + 100050 - BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
						}
					}

          if (i + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == 0)
						{
							value = value + 100000 + BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
						}
              
            ///capped 3 down
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == HPLAYER)
						{
							value = value + 10000 + BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
						}

						///capped 3 up
						if (BOARD[i - 1][j] == HPLAYER && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == 0)
						{
							value = value + 10000 - BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
						}
					}
				}

        if (i + 5 < BOARD_SIZE)
        {
          if(BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == CPLAYER)
          {
            value += 10000000;
          }
        }
        
				if (i + 4 < BOARD_SIZE)
				{
          ///capped 4 (wall up)
          if (i == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == 0)
          {
            value = value + 100050 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
          }
          
					///gapped 4 
					if (BOARD[i + 1][j] == 0 && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == CPLAYER)
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
					}

					if ((BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == 0 && BOARD[i + 3][j] == CPLAYER && BOARD[i + 4][j] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
					}

					if ((BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == 0 && BOARD[i + 4][j] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
					}
				}

				if (i + 3 < BOARD_SIZE)
				{
          ///capped 4 (wall down)
          if (i + 4 == BOARD_SIZE && BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER)
          {
            value = value + 100050 + BOARD_VALUES[i - 1][j] + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
          }
          
					///gapped 3
					if (BOARD[i + 1][j] == 0 && BOARD[i + 2][j] == CPLAYER && BOARD[i + 3][j] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
					}

					if (BOARD[i + 1][j] == CPLAYER && BOARD[i + 2][j] == 0 && BOARD[i + 3][j] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i + 1][j] + BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
					}
				}

				//diagonal down

				if (i != 0 && j != 0)
				{
					if (i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 2][j + 3] == CPLAYER && BOARD[i + 2][j + 4] == 0)
						{
							value = value + 1000000 + BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
						}
              
						///capped 4 right
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == HPLAYER)
						{
							value = value + 100050 + BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
						}

						///capped 4 left
						if (BOARD[i - 1][j - 1] == HPLAYER && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == 0)
						{
							value = value + 100050 - BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
						}
					}

          if (i + 3 < BOARD_SIZE && j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == 0)
						{
							value = value + 100000 + BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3];
							cout << "Open 3" << endl;
						}
              
            ///capped 3 down right
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == HPLAYER)
						{
							value = value + 10000 + BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3];
						}

						///capped 3 up left
						if (BOARD[i - 1][j - 1] == HPLAYER && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == 0)
						{
							value = value + 10000 - BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3];
						}
					}
				}

        if (i + 5 < BOARD_SIZE && j + 5 < BOARD_SIZE)
        {
          if(BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == CPLAYER)
          {
            value += 10000000;
          }
        }

				if (i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE)
				{
          ///capped 4 (corner up left)
          if (i == 0 && j == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == 0)
          {
            value = value + 100050 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i + 1][j + 1] == 0 && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == CPLAYER)
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
					}

					if ((BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == 0 && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
					}

					if ((BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == 0 && BOARD[i + 4][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
					}
				}

				if (i + 3 < BOARD_SIZE && j + 3 < BOARD_SIZE)
				{
          ///capped 4 (corner down right)
          if (i + 4 == BOARD_SIZE && j + 4 == BOARD_SIZE && BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER)
          {
            value = value + 100050 + BOARD_VALUES[i - 1][j - 1] + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
          }
          
					///gapped 3
					if (BOARD[i + 1][j + 1] == 0 && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3];
					}

					if (BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == 0 && BOARD[i + 3][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i + 1][j + 1] + BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3];
					}
				}

				//diagonal up
        
        if (j != 0)
				{
					if (i - 4 >= 0 && i + 1 < BOARD_SIZE && j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == 0)
						{
							value = value + 1000000 + BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
						}
              
						///capped 4 up right
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == HPLAYER)
						{
							value = value + 100050 + BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
						}

						///capped 4 down left
						if (BOARD[i + 1][j - 1] == HPLAYER && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == 0)
						{
							value = value + 100050 - BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
						}
					}

          if (i - 3 >= 0 && i + 1 < BOARD_SIZE && j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == 0)
						{
							value = value + 100000 + BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3];
						}
              
            ///capped 3 up right
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == HPLAYER)
						{
							value = value + 10000 + BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3];
						}

						///capped 3 down left
						if (BOARD[i + 1][j - 1] == HPLAYER && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == 0)
						{
							value = value + 10000 - BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3];
						}
					}
				}
        
        if (i - 5 >= 0 && j + 5 < BOARD_SIZE)
        {
          if(BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == CPLAYER)
          {
            value += 10000000;
          }
        }

				if (i - 4 >= 0 && j + 4 < BOARD_SIZE)
				{
          ///capped 4 (corner down left)
          if (i + 1 == BOARD_SIZE && j == 0 && BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == 0)
          {
            value = value + 100050 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i - 1][j + 1] == 0 && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == CPLAYER)
					{
						value = value + 100050 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
					}

					if ((BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == 0 && BOARD[i - 3][j + 3] == CPLAYER && BOARD[i - 4][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
					}

					if ((BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == CPLAYER && BOARD[i][j + 3] == 0 && BOARD[i][j + 4] == CPLAYER))
					{
						value = value + 100050 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
					}
				}
        
        ///capped 4 (corner up right)
        if (i == 0 && j + 1 == BOARD_SIZE && BOARD[i + 1][j - 1] == CPLAYER && BOARD[i + 2][j - 2] == CPLAYER && BOARD[i + 3][j - 3] == CPLAYER && BOARD[i + 4][j - 4] == 0)
        {
          value = value + 100050 + BOARD_VALUES[i + 1][j - 1] + BOARD_VALUES[i + 2][j - 2] + BOARD_VALUES[i + 3][j - 3] + BOARD_VALUES[i + 4][j - 4];
        }
        
				if (i - 3 >= 0 && j + 3 < BOARD_SIZE)
				{
					///gapped 3
					if (BOARD[i - 1][j + 1] == 0 && BOARD[i - 2][j + 2] == CPLAYER && BOARD[i - 3][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3];
					}

					if (BOARD[i - 1][j + 1] == CPLAYER && BOARD[i - 2][j + 2] == 0 && BOARD[i - 3][j + 3] == CPLAYER)
					{
						value = value + 100000 + BOARD_VALUES[i - 1][j + 1] + BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3];
					}
				}
      }
        
			else if (BOARD[i][j] == HPLAYER)
			{
				value -= BOARD_VALUES[i][j];

				//horizontal

				if (j != 0)
				{
					if (j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == 0)
						{
							value = value - 1000000 - BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
						}
              
						///capped 4 right
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == CPLAYER)
						{
							value = value - 100050 - BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] + BOARD_VALUES[i][j + 4];
						}

						///capped 4 left
						if (BOARD[i][j - 1] == CPLAYER && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == 0)
						{
							value = value - 100050 + BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
						}
					}

          if (j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == 0)
						{
							value = value - 100000 - BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3];
						}
              
            ///capped 3 right
						if (BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == CPLAYER)
						{
							value = value - 10000 - BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] + BOARD_VALUES[i][j + 3];
						}

						///capped 3 left
						if (BOARD[i][j - 1] == CPLAYER && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == 0)
						{
							value = value - 10000 + BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3];
						}
					}
				}
        
        if (j + 5 < BOARD_SIZE)
        {
          if(BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == HPLAYER)
          {
            value -= 10000000;
          }
        }

				if (j + 4 < BOARD_SIZE)
				{
          ///capped 4 (wall left)
          if (j == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == 0)
          {
            value = value - 100050 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i][j + 1] == 0 && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == HPLAYER)
					{
						value = value - 100050 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
					}

					if ((BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == 0 && BOARD[i][j + 3] == HPLAYER && BOARD[i][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
					}

					if ((BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == 0 && BOARD[i][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
					}
				}

				if (j + 3 < BOARD_SIZE)
				{
          ///capped 4 (wall right)
          if (j + 4 == BOARD_SIZE && BOARD[i][j - 1] == 0 && BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER)
          {
            value = value - 100050 - BOARD_VALUES[i][j - 1] - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3] - BOARD_VALUES[i][j + 4];
          }
          
					///gapped 3
					if (BOARD[i][j + 1] == 0 && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3];
					}

					if (BOARD[i][j + 1] == CPLAYER && BOARD[i][j + 2] == 0 && BOARD[i][j + 3] == CPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i][j + 1] - BOARD_VALUES[i][j + 2] - BOARD_VALUES[i][j + 3];
					}
				}

				//vertical

				if (i != 0)
				{
					if (i + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == 0)
						{
							value = value - 1000000 - BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
						}
              
						///capped 4 down
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == CPLAYER)
						{
							value = value - 100050 - BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] + BOARD_VALUES[i + 4][j];
						}

						///capped 4 up
						if (BOARD[i - 1][j] == CPLAYER && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == 0)
						{
							value = value - 100050 + BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
						}
					}

          if (i + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == 0)
						{
							value = value - 100000 - BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
						}
              
            ///capped 3 down
						if (BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == CPLAYER)
						{
							value = value - 10000 - BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] + BOARD_VALUES[i + 3][j];
						}

						///capped 3 up
						if (BOARD[i - 1][j] == CPLAYER && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == 0)
						{
							value = value - 10000 + BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
						}
					}
				}
        
        if (i + 5 < BOARD_SIZE)
        {
          if(BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == HPLAYER)
          {
            value -= 10000000;
          }
        }

				if (i + 4 < BOARD_SIZE)
				{
          ///capped 4 (wall up)
          if (i == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == 0)
          {
            value = value - 100050 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
          }
          
					///gapped 4 
					if (BOARD[i + 1][j] == 0 && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == HPLAYER)
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
					}

					if ((BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == 0 && BOARD[i + 3][j] == HPLAYER && BOARD[i + 4][j] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
					}

					if ((BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == 0 && BOARD[i + 4][j] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j] - BOARD_VALUES[i + 4][j];
					}
				}

				if (i + 3 < BOARD_SIZE)
				{
          ///capped 4 (wall down)
          if (i + 4 == BOARD_SIZE && BOARD[i - 1][j] == 0 && BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER)
          {
            value = value - 100050 - BOARD_VALUES[i - 1][j] - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
          }
          
					///gapped 3
					if (BOARD[i + 1][j] == 0 && BOARD[i + 2][j] == HPLAYER && BOARD[i + 3][j] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
					}

					if (BOARD[i + 1][j] == HPLAYER && BOARD[i + 2][j] == 0 && BOARD[i + 3][j] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i + 1][j] - BOARD_VALUES[i + 2][j] - BOARD_VALUES[i + 3][j];
					}
				}

				//diagonal down

				if (i != 0 && j != 0)
				{
					if (i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 2][j + 3] == HPLAYER && BOARD[i + 2][j + 4] == 0)
						{
							value = value - 1000000 - BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
						}
              
						///capped 4 right
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER && BOARD[i + 4][j + 4] == CPLAYER)
						{
							value = value - 100050 - BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] + BOARD_VALUES[i + 4][j + 4];
						}

						///capped 4 left
						if (BOARD[i - 1][j - 1] == HPLAYER && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == CPLAYER && BOARD[i + 4][j + 4] == 0)
						{
							value = value - 100050 + BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
						}
					}

          if (i + 3 < BOARD_SIZE && j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == 0)
						{
							value = value - 100000 - BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3];
						}
              
            ///capped 3 down right
						if (BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == CPLAYER && BOARD[i + 2][j + 2] == CPLAYER && BOARD[i + 3][j + 3] == HPLAYER)
						{
							value = value - 10000 - BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] + BOARD_VALUES[i + 3][j + 3];
						}

						///capped 3 up left
						if (BOARD[i - 1][j - 1] == CPLAYER && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == 0)
						{
							value = value - 10000 + BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3];
						}
					}
				}
        
        if (i + 5 < BOARD_SIZE && j + 5 < BOARD_SIZE)
        {
          if(BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER && BOARD[i + 4][j + 4] == HPLAYER)
          {
            value -= 10000000;
          }
        }

				if (i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE)
				{
          ///capped 4 (corner up left)
          if (i == 0 && j == 0 && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER && BOARD[i + 4][j + 4] == 0)
          {
            value = value - 100050 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i + 1][j + 1] == 0 && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER && BOARD[i + 4][j + 4] == HPLAYER)
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
					}

					if ((BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == 0 && BOARD[i + 3][j + 3] == HPLAYER && BOARD[i + 4][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
					}

					if ((BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == 0 && BOARD[i + 4][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
					}
				}

				if (i + 3 < BOARD_SIZE && j + 3 < BOARD_SIZE)
				{
          ///capped 4 (corner down right)
          if (i + 4 == BOARD_SIZE && j + 4 == BOARD_SIZE && BOARD[i - 1][j - 1] == 0 && BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER)
          {
            value = value - 100050 - BOARD_VALUES[i - 1][j - 1] - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3] - BOARD_VALUES[i + 4][j + 4];
          }
          
					///gapped 3
					if (BOARD[i + 1][j + 1] == 0 && BOARD[i + 2][j + 2] == HPLAYER && BOARD[i + 3][j + 3] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3];
					}

					if (BOARD[i + 1][j + 1] == HPLAYER && BOARD[i + 2][j + 2] == 0 && BOARD[i + 3][j + 3] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i + 1][j + 1] - BOARD_VALUES[i + 2][j + 2] - BOARD_VALUES[i + 3][j + 3];
					}
				}

				//diagonal up
        
        if (j != 0)
				{
					if (i - 4 >= 0 && i + 1 < BOARD_SIZE && j + 4 < BOARD_SIZE)
					{
            ///open 4
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == 0)
						{
							value = value - 1000000 - BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
						}
              
						///capped 4 up right
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == CPLAYER)
						{
							value = value - 100050 - BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] + BOARD_VALUES[i - 4][j + 4];
						}

						///capped 4 down left
						if (BOARD[i + 1][j - 1] == CPLAYER && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == 0)
						{
							value = value - 100050 + BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
						}
					}

          if (i - 3 >= 0 && i + 1 < BOARD_SIZE && j + 3 < BOARD_SIZE)
					{
						///open 3 
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == 0)
						{
							value = value - 100000 - BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3];
						}
              
            ///capped 3 up right
						if (BOARD[i + 1][j - 1] == 0 && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == CPLAYER)
						{
							value = value - 10000 - BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] + BOARD_VALUES[i - 3][j + 3];
						}

						///capped 3 down left
						if (BOARD[i + 1][j - 1] == CPLAYER && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == 0)
						{
							value = value - 10000 + BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3];
						}
					}
				}
        
        if (i - 5 >= 0 && j + 5 < BOARD_SIZE)
        {
          if(BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == HPLAYER)
          {
            value -= 10000000;
          }
        }

				if (i - 4 >= 0 && j + 4 < BOARD_SIZE)
				{
          ///capped 4 (corner down left)
          if (i + 1 == BOARD_SIZE && j == 0 && BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == 0)
          {
            value = value - 100050 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
          }
          
					///gapped 4 
					if (BOARD[i - 1][j + 1] == 0 && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == HPLAYER)
					{
						value = value - 100050 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
					}

					if ((BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == 0 && BOARD[i - 3][j + 3] == HPLAYER && BOARD[i - 4][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
					}

					if ((BOARD[i][j + 1] == HPLAYER && BOARD[i][j + 2] == HPLAYER && BOARD[i][j + 3] == 0 && BOARD[i][j + 4] == HPLAYER))
					{
						value = value - 100050 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3] - BOARD_VALUES[i - 4][j + 4];
					}
				}
        
        ///capped 4 (corner up right)
        if (i == 0 && j + 1 == BOARD_SIZE && BOARD[i + 1][j - 1] == HPLAYER && BOARD[i + 2][j - 2] == HPLAYER && BOARD[i + 3][j - 3] == HPLAYER && BOARD[i + 4][j - 4] == 0)
        {
          value = value - 100050 - BOARD_VALUES[i + 1][j - 1] - BOARD_VALUES[i + 2][j - 2] - BOARD_VALUES[i + 3][j - 3] - BOARD_VALUES[i + 4][j - 4];
        }
        
				if (i - 3 >= 0 && j + 3 < BOARD_SIZE)
				{
					///gapped 3
					if (BOARD[i - 1][j + 1] == 0 && BOARD[i - 2][j + 2] == HPLAYER && BOARD[i - 3][j + 3] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3];
					}

					if (BOARD[i - 1][j + 1] == HPLAYER && BOARD[i - 2][j + 2] == 0 && BOARD[i - 3][j + 3] == HPLAYER)
					{
						value = value - 100000 - BOARD_VALUES[i - 1][j + 1] - BOARD_VALUES[i - 2][j + 2] - BOARD_VALUES[i - 3][j + 3];
					}
				}
			}
		}
	}

	return value;
}

int maximizer(int depth, int alpha, int beta)
{
	if (depth == 0)
	{
		return compute_move_value();
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (check_empty(i, j))
			{
				BOARD[i][j] = CPLAYER;
				//cout << "Computer fakes move at: " << i << " " << j << endl;
				int rating = minimizer(depth - 1, alpha, beta);
				BOARD[i][j] = 0;

				if (rating > alpha)
				{
					alpha = rating;
					bestMoveR = i;
					bestMoveC = j;
				}

				if (alpha >= beta)
				{
					return alpha;
				}
			}
		}
	}

	return alpha;
}

int minimizer(int depth, int alpha, int beta)
{
	if (depth == 0)
	{
		return compute_move_value();
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (check_empty(i, j))
			{
				BOARD[i][j] = HPLAYER;
				//cout << "Computer fakes human move at: " << i << " " << j << endl;
				int rating = maximizer(depth - 1, alpha, beta);
				BOARD[i][j] = 0;

				if (rating <= beta)
				{
					beta = rating;
					//bestMoveR = i;
					//bestMoveC = j;
				}

				if (alpha >= beta)
				{
					return beta;
				}
			}
		}
	}

	return beta;
}