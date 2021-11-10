/*

    Si  supponga  di  disporre  di  una  scacchiera  NxN. Determinare  il  numero  di
    modi  in  cui  è  possibile posizionare Nregine in modo tale che nessuna coppia di
    regine si possa attaccare a vicenda. Quindi, una  soluzione  richiede  che  due
    regine  non  condividano  la  stessa  riga,  colonna  o  diagonale(si supponga N >3).
    
    L'input è costituito da diversi casi di test. La prima riga contiene il numero di
    casi di test.Per ogni test case è fornitounnumero intero che rappresenta N.
    
    INPUT:
        3
        4
        5
        8
    
    Per ogni test case,il programma riporti in outputil numero di modi in cui è possibile
    posizionare Nregine in modo tale che nessuna coppia di regine si possa attaccare a
    vicenda
    
    OUTPUT:
        2
        10
        92
*/
mod scacchiera_backtrack{
    //In rust ci son due tipi di array, sized e not sized.
    //Quelli sized hanno sempre bisogno della dimensione, quelli non sized invece  devono essere manipolati con una slice
    //Devo passargli unn &[tipo array].
    //Non posso fare per le matrici un & [&[type]]
    //Potrei ffare unn &[[type,size_of_col]] ma non emettere anche la prima

    //grid: empty grid.
    //Step
    pub fn backtrack(grid:&mut Vec<Vec<u32>>,step:&u32, solution_count:&mut u32){
        let mut candidates:Vec<u32>=Vec::new();
        //Se ho trovato una soluzione allora processala
        if is_a_solution(grid.len() as u32,*step){
            process_solution( grid,solution_count);
        }
        //Altrimenti
        else{
            //Costruisci i candidati
            construct_candidates(grid,&mut candidates,*step);
            for c in candidates.iter(){
                //make move
                grid[*step as usize][*c as usize]=1;
                backtrack(grid,&(step+1),solution_count);
                //unmake move
                grid[*step as usize ][*c as usize]=0;
            }
        }
    }

    fn is_a_solution(row_len:u32,step:u32)-> bool{  return step>row_len-1; }
    fn process_solution(grid:&Vec<Vec<u32>>,solution_count:&mut u32){
        /*println!("Soluzione");
        for i in 0..grid.len(){
            for j in 0.. grid.len(){
                print!("{}", grid[i][j]);
            }
            print!("\n");
        }
        print!("\n");*/
        *solution_count=*solution_count+1;
    }
    fn construct_candidates(grid:&Vec<Vec<u32>>,candidates:&mut Vec<u32>,step:u32){
        //Assumendo sia quadrata
        for i in 0..grid[step as usize].len(){
            if !is_in_column(grid,i as u32) && ! is_in_diag(grid,i as u32,step){
                    candidates.push(i as u32);
            }
        }
    }

    fn is_in_column(grid:&Vec<Vec<u32>>,num:u32)->bool{
        for i in  0..grid.len(){
            if grid[i][num as usize]!=0{
                return true;
            }
        }
        return false;
    }

    fn is_in_diag(grid:&Vec<Vec<u32>>,num:u32,step:u32)->bool{

        let first_row:i32= step as i32-1;
        let first_col:i32= num as i32-1;
        let sec_col: i32=num as i32+1;
        let mut row_idx:i32=first_row;
        let mut col_idx:i32=first_col;
        //Diagonale sinistra
        while row_idx >=0 &&col_idx>=0{
            if grid[row_idx as usize][col_idx as usize]!=0{
                return true;
            }
            row_idx=row_idx-1;
            col_idx=col_idx-1;
        }
        row_idx=first_row;
        col_idx=sec_col;
        //diagonale destra
        while row_idx >=0 &&col_idx<grid.len() as i32{
            if grid[row_idx as usize][col_idx as usize]!=0{
                return true;
            }
            println!("Row{}",row_idx);
            println!("Col{}",col_idx);
            row_idx=row_idx-1;
            col_idx=col_idx+1;
        }

        return false;
    }
}

#[cfg(test)]
mod tests {
    use crate::scacchiera_backtrack::backtrack;
    #[test]
    fn it_works() {

        let mut mat:Vec<Vec<u32>>=vec![vec![0,0,0,0],vec![0,0,0,0],vec![0,0,0,0],vec![0,0,0,0]];
        let mut mat2:Vec<Vec<u32>>=vec![vec![0,0,0,0,0],
                                        vec![0,0,0,0,0],
                                        vec![0,0,0,0,0],
                                        vec![0,0,0,0,0],
                                        vec![0,0,0,0,0]
                                        ];
        let mut mat3:Vec<Vec<u32>>=vec![vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0],
                                        vec![0,0,0,0,0,0,0,0]
                                        ];
        let mut solutions=0;
        let mut solutions2=0;
        let mut solutions3=0;
        backtrack(&mut mat,&0,&mut solutions);
        backtrack(&mut mat2,&0,&mut solutions2);
        backtrack(&mut mat3,&0,&mut solutions3);
        assert_eq!(solutions, 2);
        assert_eq!(solutions2,10 );
        assert_eq!(solutions3,92 );
    }
}
