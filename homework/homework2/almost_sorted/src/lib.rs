pub struct Heap <T: PartialOrd+Copy>{
    vector:Vec<T>,
    heap_size:usize,
    comparator: fn(&T,&T)->bool,
}

impl<T: PartialOrd+Copy> Heap<T>{

    pub fn new(initializer_array:&Vec<T>,comp:fn (&T,&T)->bool)-> Heap<T>{
        println!("HERE");
        let mut to_ret:Heap<T>=Heap{
            vector:initializer_array.clone(),
            heap_size:initializer_array.len(),
            comparator:comp,
        };
        Heap::build_heap(&mut to_ret.vector,to_ret.comparator);
        to_ret
    }

    pub fn parent(idx:usize)->usize{ if idx>0{(idx+1)/2 -1} else{0}}
    pub fn left(idx:usize)->usize{ idx*2+1}
    pub fn right(idx:usize)->usize{idx*2+2}
    pub fn size(&self)->usize{self.heap_size}
    pub fn as_vec(&self)->Vec<T>{self.vector.clone()}

    //O(logn)
    fn heapify(vector :&mut Vec<T>,start:usize,comparator:fn(&T,&T)->bool){
        let v_len=vector.len();
        if start<v_len{
            let mut largest=start;
            let sons:(usize,usize)=(Heap::<T>::left(start),Heap::<T>::right(start));
            //if sons.0 < v_len && vector[sons.0]>vector[largest]{
            if sons.0 < v_len && comparator(&vector[sons.0],&vector[largest]){
                largest=sons.0;
            }
            if sons.1  < v_len && comparator(&vector[sons.1],&vector[largest]){
                largest=sons.1;
            }
            if largest!=start{
                vector.swap(start,largest);
                //println!("Swapped {} {}",start,largest);
                Heap::heapify(vector,largest,comparator);
            }
        }
    }

    //O(n)
    fn build_heap(vector :&mut Vec<T>,comparator:fn(&T,&T)->bool){
        for i in (0..vector.len()/2).rev(){
            Heap::heapify(vector,i,comparator);
        }
    }

    //O(logn)
    pub fn insert(&mut self,value:&T){
        self.vector.push(*value);
        let mut new_idx=self.heap_size;
        let mut next_to_cmp=Heap::<T>::parent(new_idx);
        self.heap_size+=1;

        //rebuild the heap from bottom, O(logn)
        //while new_idx>=0 && (self.comparator)(&self.vector[new_idx],&self.vector[next_to_cmp]){
        while  (self.comparator)(&self.vector[new_idx],&self.vector[next_to_cmp]){
            self.vector.swap(new_idx,next_to_cmp);
            new_idx=next_to_cmp;
            next_to_cmp=Heap::<T>::parent(new_idx);
        }
    }

    //O(logn)
    pub fn extract_top(&mut self)->Option<T>{
        if self.vector.is_empty(){
            return None;
        }
        else{
            //Swap the last with the first, copy the new last (the old top) and then call heapify
            //1
            let old=self.heap_size-1;
            //1
            self.vector.swap(0,old);
            //1
            let to_ret=Some(self.vector.remove(old));
            //1
            self.heap_size -=1;
            //O(logn)
            Heap::heapify(&mut self.vector,0,self.comparator);
            to_ret
        }
    }
}
fn is_less<T:PartialOrd>(x:&T,y:&T)->bool{x<y}

//O(nlogk) k->number of inversion
pub fn heap_sort_nlogk<T:PartialOrd+Copy>(v: &mut Vec<T>,k:usize){

    //Build a min heap with the first k-1 elements
    //O(k)
    let mut heap:Heap<T>=Heap::new(&v[0..k+1].iter().cloned().collect(),is_less);
    let mut array_idx:usize=0;

    //For the last elemets of the array extract top (the minimum )
    //And insert it into the heap
    //O(2(n-k)logk)
    for idx in k+1..v.len(){
        v[array_idx]=heap.extract_top().unwrap();
        array_idx=array_idx+1;
        heap.insert(&v[idx])
    }
    //Until I have elements
    //O((n-k)logk)
    while heap.size()>0{
        v[array_idx]=heap.extract_top().unwrap();
        array_idx=array_idx+1;
    }
    println!("{}",heap.size());
}

#[cfg(test)]
mod tests {
    //use super::*;
    use crate::Heap;
    use crate::heap_sort_nlogk;
    fn compare(x:&i32,y:&i32)->bool{x>y}
    fn compare2(x:&i32,y:&i32)->bool{x<y}
    #[test]
    fn it_works() {
        /*
        let mut vec:Vec<i32>=vec![1,2,3,4,5,6,7];
        let mut my_heap:Heap<i32>=Heap::new(&vec,compare);
        my_heap.insert(&10);
        vec=my_heap.as_vec();
        println!("Parent is {}",Heap::<i32>::parent(0));
        for i in 0..vec.len(){
            println!("{} {}",i,vec[i]);
        }

        println!("The old top is {}",my_heap.extract_top().unwrap());
        vec=my_heap.as_vec();
        println!("The new heap is");
        for i in 0..vec.len(){
            println!("{} {}",i,vec[i]);
        }
        //assert_eq!((11 as f64/2 as f64).ceil() as usize,6);
        assert_eq!(2 + 1, 4);
        */
        let mut  vec:Vec<u32>=vec![2, 6, 3, 12, 56, 8];
        let mut k=3;
        heap_sort_nlogk(&mut vec,k);
        assert_eq!(vec,[2,3 ,6 ,8 ,12 ,56]);
    }
}
