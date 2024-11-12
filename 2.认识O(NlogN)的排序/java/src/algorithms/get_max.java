package algorithms;
import java.util.*;
//利用二分法查找数组最大值
//主定理:如果问题能分割为T(n) = a*T(n/b) + O(n^d)
//1.n^logb(a) > n^d => T(n) = O(n^logb(a))
//2.n^logb(a) = n^d => T(n) = O(logN*n^d)
//3.n^logb(a) < n^d => T(n) = O(n^d)
//T(n) =  2T(n/2) + O(1)
//由主定理: T(n) = O(N)

public class get_max {
	
	public static int count = 0;
	
	public static void main(String[] args){
		System.out.println("Hello World");
		int[] arr = {12,13,14,15,16,20};
		int max = process(arr,0,arr.length-1);
		System.out.println("最大值为"+max);
		
	}
	
	//arr[L..R]范围上求最大值
	public static int process(int[] arr,int L,int R) {
		count++;
		System.out.println("执行了"+count+"次");
		if (L==R) {
			return arr[L];
		}
		int mid = L + ((R-L)>>1);
		int leftMax = process(arr,L,mid);
		int rightMax = process(arr,mid+1,R);
		return Math.max(leftMax,rightMax);
	}
	
}
