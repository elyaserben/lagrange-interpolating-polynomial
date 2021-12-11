// Proyek Akhir Kelompok 9 Tomat
// Lagrange Interpolating Polynomial
// Elyaser Ben Guno (1806195135)
// Muhammad Ayyasy (1806195116)

#include<stdio.h>
#include<stdlib.h>

struct lagrange
{
	float lagrange; 			// data hasil lagrange
	struct lagrange *nextPtr; 	// pointer ke alamat data lagrange selajuntnya
};
	typedef struct lagrange Lagrange;
	typedef Lagrange *LagrangePtr;
	float koefisien_lagrange(LagrangePtr *head, LagrangePtr *tail, float num, float denum);

struct data
{	// menyimpan data x & y
	float x, y;
	struct data *next;
};
	typedef struct data Data;
	typedef Data *DataPtr;
	DataPtr headPtr, tailPtr;
	
struct hasil
{	// menyimpan hasil perhitungan
	float k, input;
	struct hasil *nextnode; 
};
	typedef struct hasil Hasil;
	typedef Hasil *HasilPtr;
	HasilPtr start = NULL;
	HasilPtr end = NULL;
	
	// fungsi-fungsi teknis
	int input_data(), sort_data(DataPtr headPtr), save(DataPtr currentPtr, float xcari);
	int cetak_data(DataPtr currentPtr), edit_data(DataPtr currentPtr);
	int cari_ganti(DataPtr currentPtr), cari_y(DataPtr currentPtr);
	
	// fungsi-fungsi untuk memori perhitungan
	void queueHasil(HasilPtr *start, HasilPtr *end, float xcari, float k);
	void dequeueHasil(HasilPtr *start, HasilPtr *end);
	void printQueue(HasilPtr currentPtr);
	
	// fungsi-fungsi tambahan
	int header(char a), header_bantuan(int b);
	int header_input(), header_lagrange();
	int ulang(), header_selesai();
	FILE *fptr;
	
	float xcari, num = 1, denum = 1, k = 0, L;
	float swapx, swapy, cari, ganti;
    int n, i, j, pilihEdit, pilihxy;
    int edit = 0, u;

int main()
{   
	char pilih;
	header(pilih);
	input_data();
	cetak_data(headPtr);
	printf("\n\tapakah anda ingin:\n\t1. lanjut\n\t2. mengganti data\n\t3. menginput ulang data");
	edit_data(headPtr);
	cari_y(headPtr);
	
	ulang();
	printf("\n\n");
	return 0;
}

//----------------------FUNGSI-FUNGSI-TAMBAHAN-------------------------------------------------------------
int header(char a)
{	// untuk tampilan awal program
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|                           |                                            |\n");
	printf("\t|===========================|                                            |\n");
	printf("\t|                        O  |                                            |\n");
	printf("\t|                       /   |      LAGRANGE INTERPOLATING POLYNOMIAL     |\n");
	printf("\t|                     -     |      =================================     |\n");
	printf("\t|                   /       |                                            |\n");
	printf("\t| O-_              /        |      KELOMPOK 9 - TOMAT                    |\n");
	printf("\t|/    \\           O         |      KELAS AL-PROG 01 (SELASA-JUMAT)       |\n");
	printf("\t|      \\         /          |                                            |\n"); 
	printf("\t|        \\    _-^           |      ANGGOTA:                              |\n");
	printf("\t|         -__-              |      ELYASER BEN GUNO (1806195135)         |\n");
	printf("\t|                           |      MUHAMMAD AYYASY (1806195116)          |\n");
	printf("\t|===========================|                                            |\n");
	printf("\t|___________________________|____________________________________________|\n");
	printf("\n\tselamat datang, apakah anda perlu bantuan? (y/n): ");
	scanf("%c", &a);
	if(a == 'y' || a == 'Y')
	{	// user butuh bantuan
		bantuan();
	}
	else if(a == 'n' || a == 'N')
	{	// lanjut ke program utama
		return 1;
	}
	else
	{	// error handling untuk input invalid
		return header(a);
	}
}

int header_bantuan(int b)
{	
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|  LAGRANGE INTERPOLATING POLYNOMIAL                              (%d/2)  |\n", b);
	printf("\t|________________________________________________________________________|\n");
}

int bantuan()
{
	int b = 1;
	header_bantuan(b);
	printf("\n\t program ini dapat digunakan untuk melakukan perhitungan lagrange interpo-");
	printf("\n\t lating polynomial untuk mencari nilai y pd titik x tertentu.\n");
	printf("\n\t lagrange interpolating polynomial merupakan sebuah metode analisis nume-");
	printf("\n\t rikal yg digunakan untuk interpolasi polinomial menggunakan polinom lag-");
	printf("\n\t range. adapun persamaan dari lagrange interpolating polynomial:\n");
	printf("\n\t           __n              ");
	printf("\n\t fn-1(x) = >_  Li(x).f(xi)  ");
	printf("\n\t           i=1\n\n\tdimana: ");
	printf("\n\t         _n_                ");
	printf("\n\t         | |  x - xj        ");
	printf("\n\t Li(x) = | |  -------       ");
	printf("\n\t         j=1  xi - xj       ");
	printf("\n\t        j!=i                ");
	
	printf("\n\n\n\t NEXT . . . ");
	getch();
	b++;
	
	header_bantuan(b);
	printf("\n\t panduan penggunaan program:");
	printf("\n\t 1. user menginput jumlah data (x,y)");
	printf("\n\t 2. user menginput nilai x dan y sebanyak jumlah data tsb");
	printf("\n\t 3. user dapat mengedit data tsb, apakah ada data yg ingin diganti, atau");
	printf("\n\t    user ingin mengganti keseluruhan data tsb");
	printf("\n\t 4. jika data yg diinput sudah fix, maka selanjutnya user dapat lanjut ke");
    printf("\n\t    perhitungan");
    printf("\n\t 5. user menginput nilai x untuk mencari nilai y pada titik x tsb");
    printf("\n\t 6. program akan melakukan perhitungan & mencetak hasil (nilai y pd titik");
    printf("\n\t    x yg diinginkan user)");
    printf("\n\t 7. setelah perhitungan selesai dilakukan, user dapat memilih apakah user");
    printf("\n\t    ingin mengulang program untuk nilai x yang lain, mengulang program u/");
    printf("\n\t    data yg lain, atau menyudahi program");

	printf("\n\n\n\t KEMBALI KE PROGRAM UTAMA . . . ");
	getch();
	
	return 1;
}

int header_input()
{
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|  INPUT DATA X & Y                                                      |\n");
	printf("\t|________________________________________________________________________|\n");
}

int header_ganti()
{
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|  EDIT DATA                                                             |\n");
	printf("\t|________________________________________________________________________|\n");
}

int header_lagrange()
{
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|  LAGRANGE INTERPOLATING POLYNOMIAL                                     |\n");
	printf("\t|________________________________________________________________________|\n");
}

int ulang()	
{	// fungsi untuk pengulangan program
	printf("\n\t----------------------------------------------------------------------------\n");
	printf("\n\tprogram telah selesai, apakah anda ingin");
	printf("\n\t1. mencari nilai y pada titik x lain\n\t2. mencoba program untuk input data yang lain\n\t3. simpan data perhitungan\n\t4. Selesai");
	
	printf("\n\tpilih antara 1, 2, 3 atau 4: ");
	scanf("%d", &u);
	if(u == 1)
	{	// mencari y pada titik x lain dengan kumpulan data yg sama
		k = 0;
		cari_y(headPtr);
		ulang();
	}
	else if(u == 2)
	{	// mengulang program dgn kumpulan data baru
		k = 0;
		return main();
	}
	else if(u == 3)
	{	
		save(headPtr, xcari);
	}
	else if(u == 4)
	{
		// program selesai
		header_selesai();
		return 1;
	}
	else
	{	// error handling untuk input invalid
		printf("\n\tinput invalid, harus 1, 2 atau 3");
		return ulang();
	}
}

int header_selesai()
{	// untuk tampilan ketika program berakhir
	system("cls");
	printf("\t--------------------------------------------------------------------------\n");
	printf("\t__________________________________________________________________________\n");
	printf("\t|                           |                                            |\n");
	printf("\t|===========================|                                            |\n");
	printf("\t|                        O  |                                            |\n");
	printf("\t|                       /   |                                            |\n");
	printf("\t|                     -     |      =================================     |\n");
	printf("\t|                   /       |      TERIMA KASIH TELAH MENGGUNAKAN        |\n");
	printf("\t| O-_              /        |      PROGRAM KAMI                          |\n");
	printf("\t|/    \\           O         |      =================================     |\n");
	printf("\t|      \\         /          |                                            |\n"); 
	printf("\t|        \\    _-^           |      KELOMPOK 9 - TOMAT:                   |\n");
	printf("\t|         -__-              |      ELYASER BEN GUNO (1806195135)         |\n");
	printf("\t|                           |      MUHAMMAD AYYASY (1806195116)          |\n");
	printf("\t|===========================|                                            |\n");
	printf("\t|___________________________|____________________________________________|\n");
}


//----------------------FUNGSI-FUNGSI-TEKNIS---------------------------------------------------------------
int input_data()
{	// fungsi untuk menginput data x dan y 
	headPtr = NULL;
	tailPtr = NULL;
	DataPtr varPtr = NULL; //Pointer yang merujuk pada variabel x dan y
	
	header_input();
	printf("\n\tmasukkan jumlah data: ");
    scanf("%d",&n);
	i = 0;
	while(i < n)
	{
        varPtr = (Data*) malloc (sizeof(Data));
        printf("\n\tmasukkan x ke-%d: ", i+1);
        scanf ("%f",&varPtr->x);
        printf("\tmasukkan y ke-%d: ", i+1);
        scanf("%f",&varPtr->y);
        
        varPtr->next = NULL;    
        if(headPtr == NULL)
		{
        	headPtr = varPtr;
		}
		else
		{
			(tailPtr)->next = varPtr;
		}
		tailPtr = varPtr;
		i++;
	}
	// setelah data diinput, data di-sort secara ascending berdasar nilai x nya
    sort_data(headPtr);
}

int sort_data(DataPtr headPtr)
{	// mengurutkan data x secara ascending (kecil ke besar), y akan mengikuti perpindahan x
	int swapped, i;
	DataPtr temp1Ptr, temp2Ptr = NULL;
	
	// sorting menggunakan bubble sort
	if(headPtr == NULL)
	{
		return 0;
	}
	do
	{
		swapped = 0;
		temp1Ptr = headPtr;
		
		while(temp1Ptr->next != temp2Ptr)
		{
			if(temp1Ptr->x > temp1Ptr->next->x)
			{
				swapx = temp1Ptr->x;
				swapy = temp1Ptr->y;
				
				temp1Ptr->x = temp1Ptr->next->x;
				temp1Ptr->y = temp1Ptr->next->y;
				
				temp1Ptr->next->x = swapx;
				temp1Ptr->next->y = swapy;
				
				swapped = 1;
			}
			temp1Ptr = temp1Ptr->next;
		}
		temp2Ptr = temp1Ptr;
	}
	while(swapped);
    
    return 1;
}

int cetak_data(DataPtr currentPtr)
{	// melakukan traversing untuk mencetak data
	i = 0;
	printf("\n\n\tdata yang dimasukkan adalah sebagai berikut:\n\n");
	printf("\t| x     |  y    |\n");
	printf("\t|-------|-------|\n");
    while(currentPtr != NULL)
    {
        printf("\t|%0.3f\t|%0.3f\t|", currentPtr->x,currentPtr->y);
        printf("\n");
        currentPtr = currentPtr->next;
        i++;
    }
    return 1;
}

int edit_data(DataPtr currentPtr)
{
	printf("\n\tpilih: ");
	scanf("%d", &pilihEdit);
	if(pilihEdit == 1)
	{	// melanjutkan program untuk mencari nilai x

		//Program di bawah digunakan untuk menyimpan data input pada file PAS-09.txt
		//Hasil penyimpanan dapat dilihat di lokasi penyimpanan C:\Users\Public\PAS-09.txt
		fptr = fopen("C:/Users/Public/PAS-09.txt","w");
	
		if(fptr == NULL)
		{
			printf("Error!");   
			exit(1);             
	   	}
		
		fprintf(fptr, "\n\n\tdata yang dimasukkan adalah sebagai berikut:\n\n");
		fprintf(fptr, "\t| x     |  y    |\n");
		fprintf(fptr, "\t|-------|-------|\n");
	    while(currentPtr != NULL)
	    {
	        fprintf(fptr, "\t|%0.3f\t|%0.3f\t|", currentPtr->x,currentPtr->y);
	        fprintf(fptr, "\n");
	        currentPtr = currentPtr->next;    
	    }
	    
	    fclose(fptr);
	    
		if(edit > 0) //menandakan telah terjadi pengeditan
		{	//mengurutkan & mencetak data hasil pengeditan
			sort_data(headPtr);
			cetak_data(headPtr);
		}
	}
	else if(pilihEdit == 2)
	{	// mengganti suatu data dengan data lain
		cari_ganti(headPtr);
	}
	else if(pilihEdit == 3)
	{	// menginput ulang data
		printf("\n\tmenginput data kembali . . .\n\n");
		input_data();
		cetak_data(headPtr);
		printf("\n\tapakah anda ingin:\n\t1. lanjut\n\t2. mengganti data\n\t3. menginput ulang data");
		edit_data(headPtr);
	}
	else
	{	// error handling untuk invalid input
		printf("\n\n\tinput invalid\n");
		return edit_data(headPtr);
	}
}

int cari_ganti(DataPtr currentPtr)
{	// mengganti suatu data dengan data lain
	// karena data berupa float, maka dilakukan pencarian data dengan tingkat presisi tertentu
	float presisi = 0.001;	
	int ada = 0;
	
	header_ganti();
	cetak_data(headPtr);
	
	printf("\n\tpilih data yang ingin di ganti: ");
	printf("\n\t1. mengganti suatu data pada kolom x");
	printf("\n\t2. mengganti suatu data pada kolom y");
	printf("\n\tpilih: ");
	scanf("%d", &pilihxy);		// pilihxy merupakan variabel u/ menyimpan pilihan kolom data yg ingin diganti
	
	if(pilihxy == 1)			
	{	// mengganti suatu data pada kolom x
		printf("\n\tangka yang ingin diganti: ");
		scanf("%f", &cari);		// cari: variabel untuk data yang ingin diganti
		printf("\tdiganti dengan          : ");
		scanf("%f", &ganti);	// ganti: variabel untuk menggantikan data yang ingin diganti
		
		for(i=0; i<n; i++)
		{
  			if((((currentPtr)->x - presisi) < cari) && (((currentPtr)->x + presisi) > cari))
   			{	// angka yang dicari ditemukan
    			ada = ada + 1; 			
				(currentPtr)->x = ganti; 	
				printf("\n\tangka %.3f berhasil diganti dengan %.3f\n", cari, ganti);
   			}
   			currentPtr = currentPtr->next;
		}
		if(ada == 0)	
		{	// angka yang dicari tidak ditemukan
			printf("\n\n\tangka %.3f tidak ditemukan pada kolom x\n", cari);
		}
		printf("\n\tapakah anda ingin:\n\t1. lanjut\n\t2. mengganti data\n\t3. menginput ulang data");
		edit = edit + 1;	//variabel edit untuk menandakan apakah sudah terjadi tindakan pengeditan atau belum
		return edit_data(headPtr);
	}
	else if(pilihxy == 2)	
	{	//mengganti suatu data pada kolom y
		printf("\n\tangka yang ingin diganti: ");
		scanf("%f", &cari);
		printf("\tdiganti dengan          : ");
		scanf("%f", &ganti);
		
		for(i=0; i<n; i++)
		{
  			if((((currentPtr)->y - presisi) < cari) && (((currentPtr)->y + presisi) > cari))
   			{
    			ada = ada + 1;
				(currentPtr)->y = ganti;
				printf("\n\tangka %.3f berhasil diganti dengan %.3f\n", cari, ganti);
   			}
   			currentPtr = currentPtr->next;
		}
		if(ada == 0)	
		{
			printf("\n\n\tangka %.3f tidak ditemukan pada kolom y\n", cari);
		}
		printf("\n\tapakah anda ingin:\n\t1. lanjut\n\t2. mengganti data\n\t3. menginput ulang data");
		edit = edit + 1;	//variabel edit untuk menandakan apakah sudah terjadi tindakan pengeditan atau belum
		return edit_data(headPtr);
	}
	else
	{
		printf("\n\n\tinput invalid\n");
		return cari_ganti(headPtr);
	}
}

int cari_y(DataPtr currentPtr)
{	// mencari nilai y pada titik x yang diinginkan user
	int tempL;
	header_lagrange();
	cetak_data(headPtr);
	
	LagrangePtr head = NULL;
	LagrangePtr tail = NULL;
	
	DataPtr loop1, loop2;
	
	printf("\n\tmasukkan nilai x untuk mencari nilai y: ");
    scanf("%f", &xcari);
    printf("\n\t==========================================================================\n");
    printf("\n\t         _n_                                            ");
	printf("\n\t         | |  x - xj                     __n            ");
	printf("\n\t Li(x) = | |  -------          fn-1(x) = >_  Li(x).f(xi)");
	printf("\n\t         j=1  xi - xj                    i=1            ");
	printf("\n\t        j!=i     \n\n");	

	i = 0;
	for(loop1 = currentPtr; loop1 != NULL; loop1 = loop1->next)
    {
    	printf("\n\t--------------------------------------------------------------------------\n");
        num = 1;
        denum = 1;
        // mencetak langkah perhitungan koefisien lagrange
        printf("\n\tL%d(%.3f) = ", i+1, xcari);
        for(loop2 = currentPtr; loop2 != NULL; loop2 = loop2->next)
        {
        	if(loop1 != loop2)
			{
        		num = num*(xcari-(loop2->x));
            	denum = denum*((loop1->x)-(loop2->x)); 
           		printf("(%.3f / %.3f) ", xcari-(loop2->x), (loop1->x)-(loop2->x));
			}
        }
        // mencari koefisien lagrange
        L = koefisien_lagrange(&head, &tail, num, denum);
        // mencetak hasil koefisien lagrange
        printf("\n\tL%d(%.3f) = %.7f", i+1, xcari, L);
        // mencetak perhitungan Li(x).f(xi)
        printf("\n\n\tL%d(%.3f).f(x%d) = (%.7f)(%.3f)", i+1, xcari, i+1, L, loop1->y);
        printf("\n\t                 = %.7f", L*(loop1->y));
        
        // hasil perhitungan disimpan pada variabel k
        k = k+(L*(loop1->y));
        i++;
    }
    printf("\n\n\n\t==========================================================================\n");
    printf("\n\tf%d(%.3f) = ", n-1, xcari);
    for(i=0; i<n; i++)
    {	// mencetak langkah perhitungan fn-1(x)
    	printf("L%d(%.3f).f(x%d) ", i+1, xcari, i+1);
    	if(i < n-1)
    	{
    		printf("+ ");
		}
	}
	// mencetak hasil y (fn-1(x)) pada titik x yang diinginkan user  
    printf("\n\n\tf%d = %f", n-1, k);	
    printf("\n\n\tnilai y pada x = %.3f adalah: %f\n\n", xcari, k);
    
    printf("\n\t==========================================================================\n");
    // memasukkan hasil perhitungan ke dalam memori secara queue
    queueHasil(&start, &end, xcari, k);
    // mencetak memori hasil perhitungan yang telah dilakukan (max. menampilkan 3 memori hasil perhitungan) 
    printQueue(start);
    return xcari;
}

float koefisien_lagrange(LagrangePtr *head, LagrangePtr *tail, float num, float denum)
{	// fungsi untuk mencari koefisien lagrange
	LagrangePtr koefisienPtr;
	koefisienPtr = (Lagrange*) malloc (sizeof(Lagrange));
	
	if(koefisienPtr != NULL)
	{
		koefisienPtr->lagrange = num/denum;
		koefisienPtr->nextPtr = NULL;
	}
	if(*head == NULL)
	{
		*head = koefisienPtr;
	}
	else
	{
		(*tail)->nextPtr = koefisienPtr;
	}
	*tail = koefisienPtr;
	
	return koefisienPtr->lagrange;
}

void queueHasil(HasilPtr *start, HasilPtr *end, float xcari, float k)
{	// fungsi untuk menambahkan hasil perhitungan ke dalam antrian
	HasilPtr hasil, currentPtr;
	hasil = (Hasil*)malloc(sizeof(Hasil));
	
	if(hasil != NULL)
	{
		hasil->k = k;
		hasil->input = xcari;
		hasil->nextnode = NULL;	
	}
	if(*start == NULL)
	{
		*start = hasil;
	}
	else
	{
		(*end)->nextnode = hasil;
	}
	*end = hasil;
	
	i = 0;
	currentPtr = *start;
	
	// memori hasil perhitungan yang ditampilkan maksimal hanya 3
	// jika lebih dari itu, hasil perhitungan yg paling lama akan di-dequeue
	while(currentPtr != NULL)
	{
		i++;
		currentPtr = currentPtr->nextnode;
		if(i>3)
		{
			dequeueHasil(start, end);
		}
	}
}

void dequeueHasil(HasilPtr *start, HasilPtr *end)
{	// fungsi untuk men-dequeue hasil perhitungan
	HasilPtr tempPtr;

	tempPtr = *start;
	*start = (*start)->nextnode;
	
	if(*start  == NULL)
	{
		*end = NULL;
	}
	
	free(tempPtr);
}

void printQueue(HasilPtr currentPtr)
{	// fungsi untuk mencetak memori hasil perhitungan
	if(currentPtr == NULL)
	{
		printf("\nhasil perhitungan saat ini kosong\n");
	}
	else
	{
		printf("\n\thistory hasil perhitungan nilai y: \n");
		printf("\t|   x   |       y       |\n");
		printf("\t|-------|---------------|");
		while (currentPtr != NULL)
		{
			printf("\n");
			printf("\t|%0.3f\t|   %0.7f\t|", currentPtr->input,currentPtr->k);
			currentPtr = currentPtr->nextnode;
		}
		printf("--> hasil saat ini");
	}
}

//Fungsi di bawah digunakan untuk menyimpan hasil perhitungan pada file PAS-09.txt.
//Hasil perhitungan dapat dilihat pada lokasi penyimpanan C:\Users\Public\PAS-09.txt
int save(DataPtr currentPtr, float xcari){
	float m;
	
	fptr = fopen("C:/Users/Public/PAS-09.txt","a");
	
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
   	}
	
	int tempL;
	header_lagrange();
	cetak_data(headPtr);
	
	LagrangePtr head = NULL;
	LagrangePtr tail = NULL;
	
	DataPtr loop1, loop2;
	
	fprintf(fptr, "\n\n\t#posisi nilai x yang akan dicari: %.3f", xcari);
    fprintf(fptr, "\n\t==========================================================================\n");
    fprintf(fptr, "\n\t         _n_                                            ");
	fprintf(fptr, "\n\t         | |  x - xj                     __n            ");
	fprintf(fptr, "\n\t Li(x) = | |  -------          fn-1(x) = >_  Li(x).f(xi)");
	fprintf(fptr, "\n\t         j=1  xi - xj                    i=1            ");
	fprintf(fptr, "\n\t        j!=i     \n\n");	

	i = 0;
	for(loop1 = currentPtr; loop1 != NULL; loop1 = loop1->next)
    {
    	fprintf(fptr, "\n\t--------------------------------------------------------------------------\n");
        num = 1;
        denum = 1;
        
        fprintf(fptr, "\n\tL%d(%.3f) = ", i+1, xcari);
        for(loop2 = currentPtr; loop2 != NULL; loop2 = loop2->next)
        {
        	if(loop1 != loop2)
			{
        		num = num*(xcari-(loop2->x));
            	denum = denum*((loop1->x)-(loop2->x)); 
           		fprintf(fptr, "(%.3f / %.3f) ", xcari-(loop2->x), (loop1->x)-(loop2->x));
			}
        }
        
        L = koefisien_lagrange(&head, &tail, num, denum);
        
        fprintf(fptr, "\n\tL%d(%.3f) = %.7f", i+1, xcari, L);
        
        fprintf(fptr, "\n\n\tL%d(%.3f).f(x%d) = (%.7f)(%.3f)", i+1, xcari, i+1, L, loop1->y);
        fprintf(fptr, "\n\t                 = %.7f", L*(loop1->y));
        
        m = m+(L*(loop1->y));
        i++;
    }
    fprintf(fptr, "\n\n\n\t==========================================================================\n");
    fprintf(fptr, "\n\tf%d(%.3f) = ", n-1, xcari);
    for(i=0; i<n; i++)
    {
    	fprintf(fptr, "L%d(%.3f).f(x%d) ", i+1, xcari, i+1);
    	if(i < n-1)
    	{
    		fprintf(fptr, "+ ");
		}
	}
	 
    fprintf(fptr, "\n\n\tf%d = %f", n-1, m);	
    fprintf(fptr, "\n\n\tnilai y pada x = %.3f adalah: %f\n\n", xcari, m);
    
    fprintf(fptr, "\n\t==========================================================================\n");
    
    fclose(fptr);
    
    return ulang();
}
