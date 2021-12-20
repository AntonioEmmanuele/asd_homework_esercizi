
pub mod sorting{

    pub trait SortingTrait<T:Eq+Ord+Copy>{
        //Return a sorted array with insertionSort
        fn insertion_sort(&self,recurvive:bool)->Vec<T>;
        //Return a sorted array with selection sort
        fn selection_sort_iterative(&self)->Vec<T>;
        //Return a sorted array with merge_sort
        fn merge_sort(&self)-> Vec<T>;
    }
    pub struct SortingObject <T:Copy+Eq+Ord>{
        array:Vec<T>,
    }

    impl <T:Copy+Eq+Ord> SortingObject<T>{

        //Generate a new instance cloning an input array
        pub fn get_sorting_object(vec:&Vec<T>)-> SortingObject<T>{
            SortingObject{
                    array:vec.clone()
            }
        }

        //changes the sorting array of the object
        pub fn change_sorting_array(&mut self,vec:&Vec<T>){
            self.array=vec.clone();
        }
    }

    impl <T:Eq+Ord+Copy> SortingTrait<T> for SortingObject<T>{

        //Iterative algo(assuming arrays starting from 0):
        //  for each element of the array starting by 1:
        //      key=array[i]                    (the actual element)
        //      j=i-1;
        //      while j>=0 and array[j]>key     ((shift position and array elements untill index is negative or the previous element is not greater than the key))
        //          array[j+1]=array[j]         (shift position)
        //          j-1; (decrement)
        //      array[j+1]=key                  (   after the while loop the key must be placed,if it never enters inn the loop then j=i-1 so j+1=i
        //                                          else it  is the first element that makes the condition false (array[j]>key)  so the right
        //                                          position for the key is j+1
        //                                          if no element make the condition false then the right position for key is 0,
        //                                          the value of j is in fact -1(-1+1=0) )
        //
        //
        //O(n^2)
        //Omega(n)
        fn insertion_sort(&self,recurvive:bool)->Vec<T>{
            let mut to_sort=self.array.clone();
            let mut key:T;
            let mut  j:i32;
            if !recurvive {

                //For each element of the array starting from 1
                for i in  1..to_sort.len(){
                    //Declare a new key, the keyy is always the actual element of the array we're evaluating
                    key=to_sort[i];
                    //Declare a new index that will consider all the previous
                    j=(i-1)as i32;
                    //Now for each previous element, starting from the index behind i
                    //if the value of the element is greater than the key value then shift the position
                    //and decrement j value
                    while j>=0 && to_sort[(j as usize)]>key {
                        to_sort[(j +1)as usize]=to_sort[(j as usize)];
                        j=j-1;
                    }
                    //replacemet of the key
                    //If we never enter in the loop(  the previous element j-1 was not greater than i)
                    //then j+1 is equal to i and this assignnment  does nothig.
                    //If we enter then there are two possibilities:
                    // 1-j is the index whose element is not greater than key,so j+1 must be the position of the key.
                    // 2- an element smaller than key was never found, correct position for key is 0, inn fact j=-1 and  new key position=-1+1
                    to_sort[(j+1) as usize]=key;
                }
            }

            /***
            with no  keys....
                while j>0 && to_sort[j-1]>to_sort[j]{
                    to_sort.swap(j-1,j);
                    j=j-1; //the last elemet is automatically handled
                }
            **/

            to_sort
        }

        //Algo(the array name is to_sort, assume the array starts from 1):
        //  n =length[array]
        //                                                                  Executed times                                   Cost
        //  For     i<- 1 to (n-1)                                             (n-1+1)                                        c1
        //      index_of_the_minimun <- findMinimumStartingFromI[i]
        //      swap(to_sort[i],to_sort[index_of_the_minimun])                  n-1                                           c6
        //  to_sort
        //  findMinimumStartingFromI[i]
        //      minimum_index<-i (initializing)                                 n-1                                           c2
        //      for j<-i to n                                             sum i<-1 to n-1 of (n-i)                            c3
        //          if to_sort[i]<minimum_index                           sum i<-1 to n-1 of n-i-1                            c4
        //                minimum_index=i                                 sum i<-1 to n-1 of   ti                             c5
        //      minimum_index
        //
        //  sum info:
        //      indexes: it is the same index of the external cycle with same bouds.( i <-1 to n-1 )
        //      argument: the number of time the cycle executes: end- start=n-1
        //  the argument of the sum is the number of times the sum is executed. it executes : n times -i because the array starts from i
        //  sum i<- 0 to n-1 of (n-i)  =   n*(n-1)-sum from i<- 0 to n-1 of i = n*(n-1)-n*(n-1)/2= n/2(2n-2-n+1)=n/2(n-1)
        //  sum i<- 0 to n-1 of (n-i-1)  =  sum i<- 0 to n-1 of (n-i) -sum i<- 0 to n-1 of 1= n(n-1)/2-(n-1)= (n-1)*(n/2-1).
        //  ti is the number of times the if cond is satisfied.
        //      best case= i is the minimum so we have 0+1 =1
        //      worst case= i is the greatest element of the sum so it always enters (n-i) times
        //  best: f(n)= nc1+(n-1) (c6+c2)+c3*n/2*(n-1)+c4*(n-1)*(n/2-1)+c5*(n-1)
        //  worst: f(n)= nc1+(n-1) (c6+c2)+c3*n/2*(n-1)+(c4+c5)*(n-1)*(n/2-1)
        //  O(n^2)=f(n)
        //  Omega(n^2)=f(n)( because independently from the if we have a n^2)
        //  Theta(n^2)=f(n) being n^2 inn both O and Omega we have that f(n)=Theta(g(n) ) <=> f(n)=O(g(n)) and f(n)=Omega(g(n))
        //  To show it's correctness the invariant will always be that array from 0 to i must be increasingly ordered for the first for cycle
        //      1-  it will be true before the cycle array[0] is increasingly ordered
        //      2-  Due to algo's working during the cycle we swap elements making the array increasingly ordered(so the cycle doesn't alter the invariant)
        //      3-  If it will always be true at the end it coincides to the increasingly ordered array, so it proves algo's correctness
        fn selection_sort_iterative (&self)-> Vec<T>{
            let mut to_sort=self.array.clone();
            let mut minimum_index;
            //For each element of the array.
            //it is length[array] -1 because, due to algo's working, the last element will surely be the greatest
            for first_cycle in 0..(to_sort.len()-1){
                //Initialize the minimum index as the actual index
                minimum_index=first_cycle;
                //Find the next minimum_index
                for nested_cycle in first_cycle..to_sort.len(){
                    //if the array in the position nested_cycle is greater than the array in the position of minimum change it
                    if to_sort[nested_cycle]<to_sort[minimum_index]{
                        minimum_index=nested_cycle;
                    }
                }
                //we've found the minimum, so now to order the array the array in position first_cycle must have the value of the actual minimum
                to_sort.swap(first_cycle,minimum_index);
            }
            //return the array
            to_sort
        }

        //Wrapper of the merge sort function
        fn merge_sort(&self)->Vec<T>{
            let mut to_sort=self.array.clone();
            merge_sort_function(&mut to_sort,0,self.array.len()-1);
            to_sort
        }

    }

    //Merge sort is based on divide/impera and combile rules.
    //divide-> Divides a sequence of n elements in two sequences of n/2 elements(if n is odd, one seq is n/2+1 len).
    //impera-> orders the two subsequences using recursion(if len(sequence)==0 then it is ordered)
    //combine-> merge the two subsequences
    //So there are two functions: merge (merges the subsequences) and merge_sort that sorts the array splitting in two subsequences.
    //algo:
    //merge_sort_function[array_to_sort,left_index,right_index]:
    //  if left>=right
    //        returnedArray<-array_to_sort
    //  middle_point<- (left+right)/2
    //  merge_sort_function[array_to_sort,left_index,middle_point]
    //  merge_sort_function[array_to_sort,middle_point+1,right_index]
    //  merge_function[]

    pub fn merge_sort_function<T:Eq+Ord+Copy>(to_sort:&mut Vec<T>,left_index:usize,right_index:usize){
            //Already sorted
            if right_index>left_index{
                //Take as an example odd seq of 11 elements and even of 10:
                //left=0 right=10 middle_point=5
                //left=0 right=9 middle_point=4
                let middle_point=(right_index+left_index )/2;
                //Now split in two subsequences and sort
                //index for odd: 0,5(6elements) 6-10(5 elements)
                //index for even: 0,4(5 elements) 5,9(5 elements)
                println!("{} {} {}",left_index,middle_point,right_index);
                merge_sort_function(to_sort,left_index,middle_point);
                merge_sort_function(to_sort,middle_point+1,right_index);
                //now merge
                merge_function(to_sort,left_index,middle_point,right_index);
            }

            else{
                println!("Ended {} {}",left_index,right_index)
            }
    }

    //Given two sub arrays: A[left_index..middle_point] and A[middle_point+1..right_index] already ordered
    //returns an new array A[left_index..right_index] ordered.
    //Algo(assuming array starts from 0):
    //  k<- size_of_first m <-size_of_second n<-size of to_sort , n >k>=m
    //                                                                          Cost                    Times
    //  size_of_first <-middle_point-left_index+1                               c1                        1
    //  size_of_second <- right_index-middle_point                              c2                        1
    //  //declare two arrays with this size                                     c3                        2(two array)
    //  for i <- 0 to size_of_first                                             c4                        k+1
    //      left_array[i]<-to_sort[i+left_index]                                c5                         k
    //  for i <- 0 to size_of_second                                            c6                        m+1
    //      right_array<- to_sort[middle_point+1+i]                             c7                          m
    //  left_array_idx,right_array_idx<-0                                       c8                         1
    //  index_for_merged<-0                                                     c16                         1
    //  while  left_array_idx<size_of_first and right_array_idx< size_of_second  c9                        n+1
    //      if left_array[left_array_idx] <=right_array[right_array_idx]        c10                        n
    //          to_sort[i]<-left_array[left_array_idx]                          c11
    //          left_array_idx<-left_array_idx+1                                c12
    //      else                                                                c13                         n
    //          to_sort[i]<-right_array[right_array_idx]                        c14
    //          right_array_idx<-right_array_idx+1                              c15
    //      index_for_merged++
    //  while left_array_idx<size_of_first                                      c17                         Worst(k+1), if this is executed then the other while is not and vice-versa
    //      to_sort[i]<-left_array[left_array_idx]                              c18
    //          left_array_idx++                                                c19
    //          index_for_merged++                                              c20

    //  while right_array_idx<size_of_second                                    c17                         Worst(m+1)
    //      to_sort[]<-left_array[right_array_idx]                              c18
    //          right_array_idx++                                               c19
    //          index_for_merged++                                              c20

    //Basically it is:(worst cases  never matters because k and m are smaller than n )
    // O(n)=fn
    // Omega(n)=fn
    // Theta(n)=fn

    fn merge_function<T:Eq+Ord+Copy>(to_sort:&mut Vec<T>,left_index:usize,middle_point:usize,right_index:usize){
        //Dimension of two helper arrays, the first contains 0 so it must be +1
        let size_of_first=middle_point-left_index+1;
        let size_of_second=right_index-middle_point;

        //init the array
        let mut left_array:Vec<T>=Vec::with_capacity(size_of_first);
        let mut right_array:Vec<T>=Vec::with_capacity(size_of_second);

        //Copy sub arrays values
        for i in 0..size_of_first{
            //Start from left
            left_array.push(to_sort[i+left_index]);
        }
        for i in 0..size_of_second{
            //Start from middle_point+1
            right_array.push(to_sort[middle_point+1+i]);
        }

        //Copy sub arrays values
        /*
            In rust:
            Should add default trait:
            let mut left_array:Vec<T>=vec![Default::default(),size_of_first];
            let mut right_array:Vec<T>=vec![Default::default(),size_of_second];
            left_array[..].clone_from_slice(to_sort[left_index..(size_of_first)]);
            right_array[..].clone_from_slice(to_sort[middle_point+1..(size_of_second)]);
        */


        //Now order the array.
        let mut left_array_idx=0;
        let mut right_array_idx=0;
        let mut index_for_merged=left_index;

        //  Until one sub array ends, this implies that one array from one specific starting point
        //  has bigger elements than the other.
        //  Then after this while in this case the code will enter ONLY in one of the two remainings while
        while left_array_idx<size_of_first && right_array_idx<size_of_second
        {
            //check for each element if it must be from left or right
            if left_array[left_array_idx]<=right_array[right_array_idx]
            {
                //assign and increment
                to_sort[index_for_merged]=left_array[left_array_idx];
                left_array_idx=left_array_idx+1;
            }
            else
            {
                //assign and increment
                to_sort[index_for_merged]=right_array[right_array_idx];
                right_array_idx=right_array_idx+1;
            }
            index_for_merged=index_for_merged+1;
        }

        //in case the first has remaining elements
        while left_array_idx < size_of_first {
            to_sort[index_for_merged] = left_array[left_array_idx];
            left_array_idx=left_array_idx+1;
            index_for_merged=index_for_merged+1;
        }

        // for the second
        while right_array_idx< size_of_second {
            to_sort[index_for_merged] = right_array[right_array_idx];
            right_array_idx=right_array_idx+1;
            index_for_merged=index_for_merged+1;
        }
    }
}
