
public class ex6_20 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		char [] v = {' ', 'T', 'A', 'C', 'G', 'G', 'G', 'T', 'A', 'T'};
		char [] w = {' ', 'G', 'G', 'A', 'C', 'G', 'T', 'A', 'C', 'G'};
		int [][]alignment = new int [v.length][w.length];
		
		System.out.print("   ");
		for(char c : w)
			System.out.printf("%3c", c);
		System.out.println();
		
		for (int i=0; i<v.length; i++)
			for(int j=0; j<w.length; j++) {				
				if(i==0 || j==0)
					alignment[i][j]=0;
				else {
					int max=0;		
					int c=0, d=0;
					if (v[i]==w[j]) {
						max = alignment[i-1][j-1] +1;						
					} else {
						max = alignment[i-1][j-1] -1;						
					}					
					c=alignment[i-1][j] -1;
					if(max<c) max=c;
					d=alignment[i][j-1] -1;
					if(max<d) max=d;
					//Local alignment
					if(max<0) max=0;
					alignment[i][j]=max;
				}
			}
		for (int i=0; i<alignment.length; i++) {
				System.out.printf("%3c", v[i]);
			for(int j=0; j<alignment[i].length; j++) {				
				System.out.printf("%3d", alignment[i][j]);
			}
			System.out.println();
		}

	}

}
