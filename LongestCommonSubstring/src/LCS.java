import java.util.ArrayList;

public class LCS {

	public static void main(String[] args) {
		LCS lcs = new LCS();
        char str1[] = "abc".toCharArray();
        char str2[] = "bcefg".toCharArray();
        System.out.println(lcs.longestCommonSubstring(str1, str2));
			
	}
	

	 public int longestCommonSubstring(char str1[], char str2[]){
		 int T[][] = new int[str1.length+1][str2.length+1];
	        
	        int max = 0;
	        for(int i=1; i <= str1.length; i++){
	            for(int j=1; j <= str2.length; j++){
	                if(str1[i-1] == str2[j-1]){
	                    T[i][j] = T[i-1][j-1] +1;
	                    if(max < T[i][j]){
	                        max = T[i][j];
	                    }
	                }
	            }
	        }
	    return max;
	}

}
