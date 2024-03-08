#include <stdio.h>
#include <stdlib.h>

// Define structure to make Bezout coefficient list
typedef struct {
  int (*bezout_coeff)[2];
  int length;
} BezoutList;

// Destory Bezout list
void destroy_bezout_list(BezoutList bezout_list) {
  free(bezout_list.bezout_coeff);
}

// Uses Bezout's Identity to get Bezout coefficients to 2x + 3y = target_score
BezoutList get_bezout_coeff(int target_num) {
  // Calculate initial coefficients
  int x0, y0;
  if (target_num % 2 == 1) {
    x0 = target_num / 2 - 1;
    y0 = 1;
  } else {
    x0 = target_num / 2;
    y0 = 0;
  }

  // Calculate memory length
  BezoutList bezout_list;
  bezout_list.length = x0 / 3 + 1;
  bezout_list.bezout_coeff = malloc(sizeof(int[bezout_list.length][2]));

  // Get all coordinate pairs
  for (int k = 0; k < bezout_list.length; k++) {
    bezout_list.bezout_coeff[k][0] = x0 - 3 * k;
    bezout_list.bezout_coeff[k][1] = y0 + 2 * k;
  }

  return bezout_list;
}

// Calculate number of possibilities from factor m with bezout co-ords (x, y) and
// (a, b) such that ax + by = m
int factor_length(int x, int y, int a, int b) {
  // Check for 0 coeff
  int x_div = 0;
  int y_div = 0;
  
  if (a == 0) {
    return y / b + 1;
  } else if (b == 0) {
    return x / a + 1;
  } else {
    x_div = x / a + 1;
    y_div = y / b + 1;
  }

  // Return minimum
  if (x_div <= y_div) {
    return x_div;
  } else {
    return y_div;
  }
}

// Compute score possibilities and print result
void compute_scores(int target_score) {
  // Get a bezout list for target_score
  BezoutList bezout_list = get_bezout_coeff(target_score);

  // Print Header
  printf("\n%-8s %-7s %-4s %-8s %-s\n", "TD+2pt", "TD+FG", "TD", "3pt FG", "Safety");

  // Make hash list to avoid repeats
  int hash_list[10000];
  for (int i = 0; i < 10000; i++) {
    hash_list[i] = -1;
  }

  // Go through each coefficient and print possibilities
  for (int k = 0; k < bezout_list.length; k++) {
    int t8, t7, t6;
    int sf = bezout_list.bezout_coeff[k][0]; // 2
    int fg = bezout_list.bezout_coeff[k][1]; // 3

    // Run through 6 possibilities (2(3) + 3(0) = 6)
    for (int a = 0; a < factor_length(sf, fg, 3, 0); a++) {
      int t60 = a, x0 = sf - 3 * a;
      // Run through 6 possibilities (2(0) + 3(2) = 6)
      for (int b = 0; b < factor_length(x0, fg, 0, 2); b++) {
	int t61 = t60 + b, y0 = fg - 2 * b;
	// Run through 7 possibilities (2(2) + 3(1) = 7)
	for (int c = 0; c < factor_length(x0, y0, 2, 1); c++) {
	  int t7 = c, x1 = x0 - 2 * c, y1 = y0 - c;
	  // Run through 8 possiblities (2(4) + 3(0))
	  for (int d = 0; d < factor_length(x1, y1, 4, 0); d++) {
	    int t80 = d, x2 = x1 - 4 * d;
	    // Run through 8 possibilities (2(1) + 3(2))
	    for (int e = 0; e < factor_length(x2, y1, 1, 2); e++) {
	      int t81 = t80 + e, x3 = x2 - e, y2 = y1 - 2 * e;

	      // Compute hash and check if unique and print if so
	      int hash = x3 * 10000 + y2 * 1000 + t61 * 100 + t7 * 10 + t81;
	      for (int i = 0; i < 10000; i++) {
		if (hash_list[i] == -1) {
		  printf("%-8d %-7d %-4d %-8d %-d\n", t81, t7, t61, y2, x3);
		  hash_list[i] = hash;
		  break;
		} else if (hash_list[i] == hash) {
		  break;
		}
	      }
	    }
	  }
	}
      }
    }
  }

  // Destroy bezout list
  destroy_bezout_list(bezout_list);
}

int main() {
  int target_score;

  while (1) {
    // Ask for score
    printf("Enter 0 or 1 to STOP\nEnter the NFL score: ");
    scanf("%d", &target_score);

    // Check for bad input to exit
    if (target_score < 2) {
      return 0;
    }

    // Otherwise compute scores and print
    compute_scores(target_score);
  }
}
