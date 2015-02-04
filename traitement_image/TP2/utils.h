
int indexN(int index, int colonnes) {
	int n = index - colonnes;
	if(n < 0) {
		return 0;
	}
	return n;
}

int indexS(int index, int lignes, int colonnes) {
	int n = index + colonnes;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}

int indexE(int index, int lignes, int colonnes) {
	int n = index + 1;
	if(n > lignes * colonnes) {
		return lignes * colonnes - 1;
	}
	return n;
}

int indexW(int index) {
	int n = index - 1;
	if(n < 0) {
		return 0;
	}
	return n;
}
