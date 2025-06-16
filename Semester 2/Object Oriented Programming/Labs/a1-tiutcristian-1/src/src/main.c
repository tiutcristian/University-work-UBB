// problem 3

#include <stdio.h>

// displays the menu
void display_menu() {
	printf("Choose an option:\n");
	printf("[1] Read a vector of numbers\n");
	printf("[2] Print Pascal triangle\n");
	printf("[3] Longest contiguous subsequence of prime numbers\n");
	printf("[4] Quit\n");
}

// computes factorial of a number
int fact(int n) {
	if (n == 0)
		return 1;
	else
		return n * fact(n - 1);
}

// computes n choose k
int comb(int n, int k) {
	return fact(n) / (fact(k) * fact(n - k));
}

// prints pascal triangle of a number
void print_pascal_triangle (int n) {
	for (int m = 1; m <= n; m++) {
		for (int k = 0; k <= m; k++) {
			printf("%d ", comb(m, k));
		}
		printf("\n");
	}
}

// checks if a number is prime
int is_prime(int n) {
	if (n < 2)
		return 0;
	if (n == 2)
		return 1;
	if (n % 2 == 0)
		return 0;
	for (int i = 3; i * i <= n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

// get the beginning and the end of the longest sequence of prime numbers
void get_seq_prime (int len, int numbers[], int *beg, int *end) {
	*beg = 0;
	*end = -1;
	int crt_beg = 0;
	int crt_end = 0;
	for (int i = 0; i < len; i++) {
		if (is_prime(numbers[i]))
			crt_end++;
		else {
			if (crt_end - crt_beg > *end - *beg) {
				*beg = crt_beg;
				*end = crt_end;
			}
			crt_beg = i + 1;
			crt_end = i;
		}
	}
	if (crt_end - crt_beg > *end - *beg) {
		*beg = crt_beg;
		*end = crt_end;
	}
}

// prints the longest sequence of prime numbers
void print_seq_prime(int len, int numbers[]) {
	int beg, end;
	get_seq_prime(len, numbers, &beg, &end);
	for (int i = beg; i <= end; i++)
		printf("%d ", numbers[i]);
	printf("\n");
}

int main() {
	int rep = 1;
	int numbers[100];
	int len_numbers = 0;
	while (rep) {
		display_menu();
		printf(">>>");
		int option;
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			printf("Reading a vector of numbers...\n");
			printf("Enter length: ");
			scanf("%d", &len_numbers);
			for (int i = 0; i < len_numbers; i++) {
				scanf("%d", &numbers[i]);
			}
			break;
		case 2:
			printf("Printing pascal triangle...\n");
			printf("n = ");
			int n;
			scanf("%d", &n);
			print_pascal_triangle(n);
			break;
		case 3:
			printf("Printing the longest contiguous subsequence of prime numbers...\n");
			if (len_numbers == 0) {
				printf("No numbers in the vector !!\n");
				continue;
			}
			print_seq_prime(len_numbers, numbers);
			break;
		case 4:
			printf("Bye! \n\n");
			rep = 0;
			break;
		default:
			break;
		}
	}
	return 0;
}