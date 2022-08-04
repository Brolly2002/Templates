class KMP {

	public :
		vector<int> LPS;
		vector<int> Z;
		int n;
		
		KMP(int _n) : n(_n) {
			LPS.resize(n);
			Z.resize(n);
			for(int i = 0; i < n; i ++) Z[i] = LPS[i] = 0;
		}
		
		void Construct_Lps(string s) {
			int i = 1, Len = 0;
			while(i < s.size()) {
				if(s[i] == s[Len]) {
					Len ++;
					LPS[i] = Len;
					i ++;
				}
				else {
					if(Len > 0) Len = LPS[Len - 1];
					else LPS[i] = 0, i ++;
				}
			}
		}
		
		void Construct_Z(string s) {
			int L = 0, R = 0;
			for(int i = 1; i < s.size(); i ++) {
				if(i <= R) Z[i] = min(R - i + 1, Z[i - L]);
				while(s[Z[i]] == s[i + Z[i]]) Z[i] ++;
				if(i + Z[i] - 1 > R) L = i, R = i + Z[i] - 1;
			}
		}
		
		int Get_Lps(int i) {
			return LPS[i];
		}
		
		int Get_Z(int i) {
			return Z[i];
		}
};