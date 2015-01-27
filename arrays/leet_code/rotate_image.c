/*

Rotate image

*/

1 2 
3 4


void rotate(vector<vector<int>>& matrix) {
        const int n = matrix.size();

        for(int i = 0 ;i < n/2 ; ++i)
        	for (int j = 0; j < n; ++j)
        	 	swap( matrix[i][j], matrix[n - 1 - i][j] );


3 4 
1 2 



        	 for(int i = 0;i < n ; ++i)
        	 	for (int j = i + 1; j < n; ++j)
        	 		swap(matrix[i][j], matrix[j][i]);

2 1
4 3


}