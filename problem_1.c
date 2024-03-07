#include <stdio.h>
#include <strings.h>

// Get the data to print
float monthly_sales[] = {23458.01, 40112.00, 56011.85, 37820.88, 37904.67, 60200.22, 72400.31, 56210.89, 67230.84, 68233.12, 80950.34, 95225.22};

// Months of the year to print
char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Print sales report
void print_sales_report() {
  //Print header
  printf("Monthly Sales Report:\n\n");
  printf("%-10s Sales\n", "Month");

  // Itterate over months and print month result
  for (int i = 0; i < 12; i++)
    printf("%-10s $%.2f\n", months[i], monthly_sales[i]);

  // Print Spacing
  printf("\n\n");
}

// Print sales summary
void print_sales_summary() {
  // Print header
  printf("Sales summary:\n\n");

  int min_sales_index = 0;
  int max_sales_index = 0;
  float cum_sales = 0.;

  // Itterate over months and get results
  for (int i = 0; i < 12; i++) {
    // Check set minimum
    if (monthly_sales[i] < monthly_sales[min_sales_index])
      min_sales_index = i;

    // Check set maximum
    if (monthly_sales[i] > monthly_sales[max_sales_index])
      max_sales_index = i;

    // Add to cummulitive sales
    cum_sales += monthly_sales[i];
  }

  // Get average
  float average_sales = cum_sales / 12.;

  // Print Results
  printf("%-15s $%-10.2f (%s)\n", "Minimum sales:", monthly_sales[min_sales_index], months[min_sales_index]);
  printf("%-15s $%-10.2f (%s)\n", "Maximum sales:", monthly_sales[max_sales_index], months[max_sales_index]);
  printf("%-15s $%-10.2f\n\n\n", "Average sales:", average_sales);
}

// Print highest to lowest
void print_highest_to_lowest() {
  // Print header
  printf("Monthly Sales Report (Highest to Lowest):\n\n");
  printf("%-10s Sales\n", "Month");

  // Make an index array of highest to lowest sales
  int index_arr[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

  // Itterate over months
  for (int m_index = 0; m_index < 12; m_index++) {
    for (int i = 0; i < 12; i++) {
      // Itterate over the index_arr until you hit and element that is bigger or end of list
      if (index_arr[i] == -1) {
	// Append if end of list
	index_arr[i] = m_index;
	break;
      } else if (monthly_sales[index_arr[i]] < monthly_sales[m_index]) {
	// If the entry in the array is the bigger than current, shift the arr right and insert element
	for (int j = 11; j > i; j--)
	  index_arr[j] = index_arr[j - 1];
	index_arr[i] = m_index;
	break;
      }
    }
  }

  // Print results
  for (int i = 0; i < 12; i++)
    printf("%-10s $%.2f\n", months[index_arr[i]], monthly_sales[index_arr[i]]);
}

int main() {
  // Print reports in order
  print_sales_report();
  print_sales_summary();
  print_highest_to_lowest();
}
