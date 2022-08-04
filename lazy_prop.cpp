template <typename T>
class lazy_segment_tree {
   int size;
   vector<T> data;
   vector<T> lazy;
   public:
   lazy_segment_tree(int _size) {
      size = 1;
      while (size < _size) size *= 2;
      data = vector<T>(size * 2);
      lazy = vector<T>(size * 2, -1);
   }
   
   void down(int cur, int l, int r) {
      if (!lazy[cur]) return;
      int cl = cur * 2, cr = cur * 2 + 1;
      T diff = lazy[cur] * (r - l) / 2;
      data[cl] = diff;
      data[cr] = diff;
      lazy[cl] = lazy[cur];
      lazy[cr] = lazy[cur];
      lazy[cur] = 0;
   }
   
   T query(int left, int right, int cur, int l, int r) {
      if(left <= l && r <= right) {
         return data[cur];
      }
      else if (left >= r || l >= right) return 0;
      else {
         down(cur, l, r);
         int mid = (l + r) / 2;
         int cl = cur * 2, cr = cur * 2 + 1;
         T ql = query(left, right, cl, l, mid);
         T qr = query(left, right, cr, mid, r);
         return ql + qr;
      }
   }
   
   T Query(int left, int right) {
      return query(left, right, 1, 0, size);
   }
   
   void update(int left, int right, T val, int cur, int l, int r) {
      if (left <= l && r <= right) {
         lazy[cur] = val;
         data[cur] = val * (r - l);
      }
      else if (left >= r || l >= right) return;
      else {
         down(cur, l, r);
         int mid = (l + r) / 2;
         int cl = cur * 2, cr = cur * 2 + 1;
         update(left, right, val, cl, l, mid);
         update(left, right, val, cr, mid, r);
         data[cur] = data[cl] + data[cr];
      }
   }
   
   void Update(int left, int right, T val) {
      update(left, right, val, 1, 0, size);
   }
};