package algorithms;

public class mergeSsort {
	public static void main(String[] args) {
		int[] arr = {20,12,17,5,12,13,11,5,14};
		process(arr,0,arr.length-1);
		for (int i : arr) {
			System.out.println(i);
		}
	}
	
	public static void process(int[] arr,int L,int R) {
		if (L==R) return;
		int mid = L + (R-L)/2;
		process(arr,L,mid);
		process(arr,mid+1,R);
		merge(arr,L,mid,R);
	}
	
	public static void merge(int[] arr,int L,int mid,int R) {
		int p1 = L;
		int p2 = mid+1;
		int[] help = new int[R-L+1];
		int i = 0;
		while (p1<=mid&&p2<=R) {
			help[i++] = (arr[p1]<=arr[p2] ? arr[p1++] : arr[p2++]); 
		}
		while (p1<=mid) {
			help[i++] = arr[p1++];
		}
		while (p2<=R) {
			help[i++] = arr[p2++];
		}
		for (i=0;i<help.length;++i) {
			arr[L+i] = help[i];//注意是L+i，拷贝的是L~R部分
		}
	}
}
