
pub mod sorting;


#[cfg(test)]
mod tests {
    use crate::sorting::sorting::SortingObject;
    use crate::sorting::sorting::SortingTrait;

    #[test]
    fn test_insertion_iterative() {
        let to_sort=vec![2 ,7 ,5 ,1];
        let mut to_sort= SortingObject::get_sorting_object(&to_sort);
        let mut sorted=to_sort.insertion_sort(false);
        assert_eq!(vec![1,2,5,7],sorted);
        to_sort.change_sorting_array(&vec![10,2,200,21,33,68]);
        sorted=to_sort.insertion_sort(false);
        assert_eq!(vec![2,10,21,33,68,200],sorted);
    }

    #[test]
    fn test_selection_iterative() {
        let to_sort=vec![2 ,7 ,5 ,1];
        let mut to_sort= SortingObject::get_sorting_object(&to_sort);
        let mut sorted=to_sort.selection_sort_iterative();
        assert_eq!(vec![1,2,5,7],sorted);
        to_sort.change_sorting_array(&vec![10,2,200,21,33,68]);
        sorted=to_sort.selection_sort_iterative();
        assert_eq!(vec![2,10,21,33,68,200],sorted);
    }

    #[test]
    fn merge_sort() {
        let to_sort=vec![2 ,7 ,5 ,1];
        let mut to_sort= SortingObject::get_sorting_object(&to_sort);
        let mut sorted=to_sort.merge_sort();
        assert_eq!(vec![1,2,5,7],sorted);
        to_sort.change_sorting_array(&vec![10,2,200,21,33,68]);
        sorted=to_sort.merge_sort();
        assert_eq!(vec![2,10,21,33,68,200],sorted);
    }
}
