#include <iostream>

using namespace std;

// Number of Men or Women

#define N 4

// This function returns true if woman 'w' prefers man 'm1' over man 'm'

bool w_prefer_mATUAL_over_mNOVO(int prefer[2 * N][N],
                                int w,
                                int mATUAL,
                                int mNOVO) {
  // Check if w prefers mNOVO over her current engagment m1ATUAL

  for (int i = 0; i < N; i++) {
    // If mATUAL comes before mNOVO in the list of w,
    // then w prefers her current engagement, don't do anything

    if (prefer[w][i] == mATUAL)

      return true;

    // If mNOVO cmes before mATUAL in w's list, then free her current
    // engagement and engage her with m

    if (prefer[w][i] == mNOVO)
      return false;
  }
}

// Prints stable matching for N boys and N girls. Boys are numbered as 0 to N-1.
// Girls are numbered as N to 2N-1.

void stableMarriage(int prefer[2 * N][N]) {
  /*
   Stores partner of women. This is our output array that stores information.
   The value of wPartner[I] indicates the partner assigned to woman N+i.
   Note that the woman numbers between N and 2*N-1.
   The value -1 indicates that (N+i)'th woman is free
  */

  int wPartner[N];

  // An array to store availability of men. If mFree[i] is true,
  // then man 'i' is free, otherwise engaged.

  bool mFree[N];

  // Initialize all men and women as free

  for (int i = 0; i < N; i++) {
    wPartner[i] = -1;
    mFree[i] = true;
  }

  int freeCount = N;

  // While there are free men

  while (freeCount > 0) {
    // Pick the first free man (we could pick any)

    int m;

    for (m = 0; m < N; m++)

      if (mFree[m] == true)

        break;

    // One by one go to all women according to m's preferences.
    // Here m is the picked free man

    for (int i = 0; i < N && mFree[m] == true; i++) {
      int w = prefer[m][i];

      // The woman of preference is free, w and m become partners.
      // So we can say they are engaged not married

      if (wPartner[w - N] == -1) {
        wPartner[w - N] = m;

        mFree[m] = false;

        freeCount--;
      }

      else  // If w is not free
      {
        // Find current engagement of w

        int m1 = wPartner[w - N];

        // If w prefers m over her current engagement m1,
        // then break the engagement between w and m1 and engage m with w.

        if (w_prefer_mATUAL_over_mNOVO(prefer, w, m1, m) == false) {
          wPartner[w - N] = m;

          mFree[m] = false;

          mFree[m1] = true;
        }
      }

    }  // End of the for loop that goes to all women in m's list
  }    // End of the main while loop

  // Print the solution

  cout << "Woman   Man" << endl;

  for (int i = 0; i < N; i++)
    cout << " " << i + N << "\t" << wPartner[i] << endl;
}

// Driver program to test above functions

int main() {
  int prefer[2 * N][N] = {
      {7, 5, 6, 4},

      {5, 4, 6, 7},

      {4, 5, 6, 7},

      {4, 5, 6, 7},

      {0, 1, 2, 3},

      {0, 1, 2, 3},

      {0, 1, 2, 3},

      {0, 1, 2, 3},
  };

  stableMarriage(prefer);

  return 0;
}