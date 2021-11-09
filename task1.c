// Buzea Alexandru-Mihai-Iulian 311CAb

// Returns the value of a byte given the unsigned value of that byte.
char byte_value(unsigned char byte)
{
	if (byte < 128)
		return byte;
	else
		return byte - 256;
}

double shield_charge(int n, int *m, int **v)
{
	long sum = 0;
	unsigned char *byte;

	// Summation of the first-line bytes.
	for (int j = 0; j < *m; ++j) {
		for (unsigned long k = 0; k < sizeof(int); ++k) {
			byte = ((unsigned char *)(*v + j)) + k;
			sum += (long)byte_value(*byte);
		}
	}

	// Summation of the last-line bytes.
	for (int j = 0; j < *(m + n - 1); ++j) {
		for (unsigned long k = 0; k < sizeof(int); ++k) {
			byte = ((unsigned char *)(*(v + n - 1) + j)) + k;
			sum += (long)byte_value(*byte);
		}
	}

	// Summation of the first-column bytes.
	for (int i = 1; i < n - 1; ++i) {
		byte = ((unsigned char *)(*(v + i)));
		sum += (long)byte_value(*byte);
	}

	// Summation of each last byte on a line.
	for (int i = 1; i < n - 1; ++i) {
		byte = ((unsigned char *)(*(v + i) + *(m + i) - 1)) + sizeof(int) - 1;
		sum += (long)byte_value(*byte);
	}

	// Calculating the total number of bytes gradually.
	unsigned long num = *m * sizeof(int); // Bytes on the first line.
	num += *(m + n - 1) * sizeof(int); // Bytes on the last line.
	num += (unsigned long)(2 * (n - 2)); // Bytes on columns.
	return (double)sum / num; // Last division (don't forget the cast).
}
