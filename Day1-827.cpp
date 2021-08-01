class Solution {
public:
    // TIME COMPLEXITY:- O(n*m*log(n*m))
    // SPACE COMPLEXITY:- O(n*m)
    #define F first
    #define S second
    #define pii pair<int,int>
    vector<pair<int,int>> parent; // {parent,rank}
    vector<int> cmp_size;
    // every cell has unique identity, (i,j) --> i*m + j;
    // find set function with path compresssion
    int find_set(int x){
        if(parent[x].F==x)
            return x;
        return parent[x].F = find_set(parent[x].F);
    }
    // union set function with rank compression
    void union_set(int x,int y){
        int xroot = find_set(x);
        int yroot = find_set(y);
        if(xroot==yroot)
            return;
        if(parent[xroot].S==parent[yroot].S)
            parent[xroot].S++; // increment the rank when rank of the two components are same
        if(parent[xroot].S>parent[yroot].S)
            parent[yroot].F = xroot, cmp_size[xroot]+=cmp_size[yroot]; // increment the size of the connected component on union
        else
            parent[xroot].F = yroot, cmp_size[yroot]+=cmp_size[xroot]; // increment the size of the connected component on union
 
    }
    int largestIsland(vector<vector<int>>& mat) {
        int n = mat.size(),m = mat[0].size();
        for(int i=0;i<n*m;i++){
            parent.push_back({i,0});
            cmp_size.push_back(0);
            if(mat[i/m][i%m])
                cmp_size[i]++;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i+1<n and mat[i][j] and mat[i+1][j])
                    union_set(i*m+j,(i+1)*m+j);
                if(i-1>=0 and mat[i][j] and mat[i-1][j])
                    union_set(i*m+j,(i-1)*m+j);
                if(j+1<m and mat[i][j] and mat[i][j+1])
                    union_set(i*m+j,i*m+j+1);
                if(j-1>=0 and mat[i][j] and mat[i][j-1])
                    union_set(i*m+j,i*m+j-1);
            }
        }
        int ans = 0;
        unordered_set<int> distinct;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]){
                    ans = max(ans,cmp_size[i*m+j]);
                    continue;
                }
                int curr_ans = 1;
                distinct.clear();
                if(i+1<n and mat[i+1][j])
                    distinct.insert(find_set((i+1)*m+j));
                if(i-1>=0 and mat[i-1][j])
                    distinct.insert(find_set((i-1)*m+j));
                if(j+1<m and mat[i][j+1])
                    distinct.insert(find_set(i*m+j+1));
                if(j-1>=0 and mat[i][j-1])
                    distinct.insert(find_set(i*m+j-1));
                for(auto f:distinct)
                    curr_ans+=cmp_size[f];
                ans = max(ans,curr_ans);
            }
        }
        return ans;
    }
};