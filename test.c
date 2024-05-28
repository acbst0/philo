#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef	struct test
{
	int number;
	pthread_t	tr;

}test;

// İş parçacığı fonksiyonlarından biri
void* print_numbers(void* arg) {
    for(int i = 0; i < 10; i++) {
        printf("Sayı: %d\n", i);
        sleep(1); // Her sayıdan sonra 1 saniye bekle
    }
    return NULL;
}

// Diğer iş parçacığı fonksiyonu
void* print_hello_world(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("Merhaba Dünya\n");
        sleep(2); // Her mesajdan sonra 2 saniye bekle
    }
    return NULL;
}

int main() {
    test	*test1;
	test	*test2;

	test1 = (test *)malloc(sizeof(test));
	test2 = (test *)malloc(sizeof(test));
	test1->number = 1;
	test2->number = 2;
    // İlk iş parçacığını oluştur
    if(pthread_create(&test1->tr, NULL, print_numbers, NULL) != 0) {
        fprintf(stderr, "İş parçacığı oluşturulamadı\n");
        return 1;
    }

    // İkinci iş parçacığını oluştur
    if(pthread_create(&test2->tr, NULL, print_hello_world, NULL) != 0) {
        fprintf(stderr, "İş parçacığı oluşturulamadı\n");
        return 1;
    }

    // İş parçacıklarının bitmesini bekle
    pthread_join(test1->tr, NULL);
    pthread_join(test2->tr, NULL);

    printf("Tüm iş parçacıkları tamamlandı\n");
    return 0;
}
