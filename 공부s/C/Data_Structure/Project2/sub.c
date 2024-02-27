int ArrayMax(int* a, int n) {
	int tmp = a[0];
	for (int i = 0; i < n; i++) {
		if (tmp < a[i]) {
			tmp = a[i];
		}
	}
	return tmp;
}