// Insertion Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"

void InsertionSort(std::vector<int>* numbers, int &comparisons, int &memaccess) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap

   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         if(j>0){ // check if second statement is evaluated
            comparisons++; // increment comparisons
            memaccess+=2; // increment memory access
         }

         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         memaccess++; // increment memory access
         (*numbers)[j] = (*numbers)[j - 1];
         memaccess += 2; // increment memory access
         (*numbers)[j - 1] = temp;
         memaccess++; // increment memory access
         --j;
      }
      if(j>0){ // verify whether second statement of while loop was evaluated
        comparisons++; // increment comparisons
        memaccess+=2; // increment memory access
      }
   }

   return;
}
