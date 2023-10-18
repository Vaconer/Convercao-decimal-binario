#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Valores {
    int mantissa;
    int menor_valor;
    int maior_valor;
    double numeros_decimais;
};

struct Valores valores_inseridos[10000]; 
int contador_valores = 0; 

//____________________________________INSERIR E MOSTRAR VALORES_____________________________________________________________
void inserir_valores() {
    struct Valores novo_valor;

    printf("Mantissa (n): ");
    scanf("%d", &novo_valor.mantissa);

    printf("Menor valor (l): ");
    scanf("%d", &novo_valor.menor_valor);

    printf("Maior valor (u): ");
    scanf("%d", &novo_valor.maior_valor);

    printf("Numeros em base decimal: ");
    scanf("%lf", &novo_valor.numeros_decimais);

    valores_inseridos[contador_valores++] = novo_valor;
    getchar(); // Enter
    getchar(); //  Enter
    system("cls"); 
}

void mostrar_valores() {
    if (contador_valores == 0) {
        printf("Nenhum valor inserido ainda.\n");
    } else {
        printf("Valores inseridos:\n");
        for (int i = 0; i < contador_valores; i++) {
            printf("%d) Mantissa: %d \n   Menor valor: %d \n   Maior valor: %d \n   Numeros em base decimal: %.10lf\n\n",
                   i + 1, valores_inseridos[i].mantissa, valores_inseridos[i].menor_valor,
                   valores_inseridos[i].maior_valor, valores_inseridos[i].numeros_decimais);
        }
    }
}

//____________________________________INSERIR E MOSTRAR VALORES_____________________________________________________________

//___________________________________DECIMAL BINARIO______________________________________________________________________

void decimal_binario(double numeros_decimais) {
    if (numeros_decimais == 0) {
        printf("0");
        return;
    }

    int parte_inteira = (int)numeros_decimais; // parte inteira
    double parte_fracionaria = numeros_decimais - parte_inteira; // parte fracionada

    // Converter a parte inteira
    if (parte_inteira == 0) {
        printf("0");
    } else {
        int binario_parte_inteira[64];
        int indice = 0;
        while (parte_inteira > 0) {
            binario_parte_inteira[indice++] = parte_inteira % 2; // pegar o resto
            parte_inteira /= 2; // dividir por 2
        }
        for (int i = indice - 1; i >= 0; i--) {
            printf("%d", binario_parte_inteira[i]);
        }
    }

    // Converter parte fracionária para binário
    if (parte_fracionaria > 0) {
        printf(".");
        while (parte_fracionaria > 0) {
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;
            printf("%d", bit);
            parte_fracionaria -= bit;
        }
    }
}

void binario_decimal(double numeros_decimais) {
    double resultado = 0.0;
    int binario_parte_inteira[64];
    int indice = 0;

    int parte_inteira = (int)numeros_decimais; // parte inteira
    double parte_fracionaria = (numeros_decimais - parte_inteira); // parte fracionária

    // Converter a parte inteira
    if (parte_inteira == 0) {
        //teste
    } else {
        while (parte_inteira > 0) {
            binario_parte_inteira[indice++] = parte_inteira % 2; // pegar o resto
            parte_inteira /= 2; // dividir por 2
        }
        for (int i = 0; i < indice; i++) {
            resultado += binario_parte_inteira[i] * pow(2, i);
        }
        printf("%.0lf", resultado/10);
    }

    // Converter parte fracionária para binário
    // PROBLEMA: ESTÁ PRINTANDO O 0 DA PARTE FRACIONARIA !!!
    if (parte_fracionaria > 0) {
        double resultado_fracionaria = 0;
        int potencia = -1; // Começa em -1
        int casas_decimais = 0;

        int imprimindo_fracionaria = 0; // Variável de controle

        while (casas_decimais < 10) { // número de casas decimais desejadas aqui
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;

            if (imprimindo_fracionaria || bit == 1) {
                resultado_fracionaria += bit * pow(2, potencia);
                imprimindo_fracionaria = 1; // Começa a imprimir a partir do primeiro dígito significativo
            }

            parte_fracionaria -= bit;
            potencia--;
            casas_decimais++;
        }
        printf("%.10lf", resultado_fracionaria); // Imprime 10 casas decimais
    }
}

void binario_decimal_negativo(double numeros_decimais) {
    double resultado = 0.0;
    int binario_parte_inteira[64];
    int indice = 0;

    numeros_decimais = numeros_decimais * (-1);

    int parte_inteira = (int)numeros_decimais; // parte inteira
    double parte_fracionaria = numeros_decimais - parte_inteira; // parte fracionária

    // Verificar o sinal "-" apenas se a parte inteira for diferente de zero
    if (parte_inteira != 0) {
        printf("-");
        parte_inteira = abs(parte_inteira); // Usar o valor absoluto da parte inteira
    }
    else{
        printf("-");
    }
    

    // Converter a parte inteira
    if (parte_inteira == 0 && parte_fracionaria < 1) {
        // Não imprime nada antes do ponto decimal
    } else {
        while (parte_inteira > 0) {
            binario_parte_inteira[indice++] = parte_inteira % 2; // pegar o resto
            parte_inteira /= 2; // dividir por 2
        }
        for (int i = 0; i < indice; i++) {
            resultado += binario_parte_inteira[i] * pow(2, i);
        }
        printf("%.0lf", resultado/10);
    }

    // Converter parte fracionária para binário
    // PROBLEMA: ESTÁ PRINTANDO O 0 DA PARTE FRACIONARIA !!!
    if (parte_fracionaria > 0) {
        if (parte_inteira != 0) {
            printf(".");
        }
        double resultado_fracionaria = 0;
        int potencia = -1; // Começa em -1
        int casas_decimais = 0;

        while (casas_decimais < 10) { // Altere o número de casas decimais desejadas aqui
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;
            resultado_fracionaria += bit * pow(2, potencia);
            parte_fracionaria -= bit;
            potencia--;
            casas_decimais++;
        }
        printf("%.10lf", resultado_fracionaria); // Imprime 10 casas decimais
    }
}

//___________________________________DECIMAL BINARIO______________________________________________________________________

//___________________________________NORMALIZAR BINARIO PARTE______________________________________________________________________
int contar_binario(double numeros_decimais, int *posicaoPonto) {
    int count = 0;

    if (numeros_decimais == 0) {
        return 1;
    }

    int parte_inteira = (int)numeros_decimais;
    double parte_fracionaria = numeros_decimais - parte_inteira;

    // Contar dígitos da parte inteira
    while (parte_inteira > 0) {
        parte_inteira /= 2;
        count++;
    }

    // Contar dígitos da parte fracionada
    int posicao = 0;
    while (parte_fracionaria > 0) {
        parte_fracionaria *= 2;
        int bit = (int)parte_fracionaria;
        parte_fracionaria -= bit;
        count++;
        posicao++;
        if (bit == 1) {
            *posicaoPonto = posicao;
            break;
        }
    }

    return count;
}

void normalizar_binario(double numeros_decimais, int posicaoPonto, int tamanho, int menor_valor, int maior_valor, int mantissa) {
    if (posicaoPonto != -1) {
        printf("\n- Numero normalizado com ponto: 0.");

        // Imprimir os números após o primeiro 1
        int parte_inteira = (int)numeros_decimais;
        double parte_fracionaria = numeros_decimais - parte_inteira;
        int posicao_mantissa = 0;
        int encontrou_primeiro_1 = 0;

        while (posicao_mantissa < mantissa) {
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;

            // Imprimir somente após o primeiro "1" ser encontrado
            if (bit == 1 && encontrou_primeiro_1 == 0) {
                printf("1");
                encontrou_primeiro_1 = 1;
            } else if (encontrou_primeiro_1 == 1) {
                printf("%d", bit);
            }

            parte_fracionaria -= bit;
            posicao_mantissa++;
        }

        int expoente = posicaoPonto - (encontrou_primeiro_1 ? 1 : 0);

        printf(" * 2^%d", expoente*(-1));

        if (expoente > maior_valor) {
            printf("  (UNDERFLOW)");
        }
        if (expoente < menor_valor) {
            printf("  (OVERFLOW)");
        }

        printf(" *Mantissa:%d", mantissa);
    }
}

void normalizar_com_parte_inteira(double numeros_decimais, int parte_inteira, int menor_valor, int maior_valor, int mantissa) {
    
    printf("\n- Numero normalizado com parte inteira: ");
    
    printf("0.");
    
    // Converter a parte inteira para binário
    int binario_parte_inteira[64];
    int indice = 0;

    while (parte_inteira > 0) {
        binario_parte_inteira[indice++] = parte_inteira % 2; // pegar o resto
        parte_inteira /= 2; // dividir por 2
    }

    for (int i = indice - 1; i >= 0; i--) {
        printf("%d", binario_parte_inteira[i]);
    }

    // Normalizar o número com parte inteira
    double parte_fracionaria = numeros_decimais - (int)numeros_decimais;
    int posicao_mantissa = 0;
    int encontrou_primeiro_1 = 0;

    while (posicao_mantissa < mantissa) { 
        parte_fracionaria *= 2;
        int bit = (int)parte_fracionaria;
        parte_fracionaria -= bit;

        // Imprimir somente após o primeiro "1" ser encontrado
        if (bit == 1 && encontrou_primeiro_1 == 0) {
            printf("1");
            encontrou_primeiro_1 = 1;
        } else if (encontrou_primeiro_1 == 1) {
            printf("%d", bit);
        }

        posicao_mantissa++;
    }

    // Verificar se houve truncamento
    printf(" * 2^%d", indice);

    if (indice > maior_valor) {
        printf("  (OVERFLOW) ");
    }
    if (indice < menor_valor) {
        printf("  (UNDERFLOW) ");
    }

    printf(" *Mantissa:%d", mantissa);

    printf("\n");
}


//-------------------------------------------------------------------------------------------------------------------------------------
void normalizar_binario_negativo_SA(double numeros_decimais, int posicaoPonto, int tamanho, int menor_valor, int maior_valor, int mantissa) {
    // Multiplicar números_decimais por -1
    numeros_decimais = (numeros_decimais * -1) + 1;

    if (posicaoPonto != -1) {
        int casasDeslocadas = posicaoPonto;
        printf("\n- Numero normalizado negativo (SA): ");
        printf("1 ");

        // Preencher com zeros até a posição do primeiro 1
        int posicaoFinal = tamanho - posicaoPonto;
        for (int i = 0; i < posicaoFinal; i++) {
            printf("1 ");
        }

        // Colocar o 1 na posição do primeiro 1
        printf("1");

        int expoente;
        int parteMantissa = 0; // Variável para contar os bits impressos

        expoente = -casasDeslocadas;

        // Variável para marcar que o primeiro "1" foi encontrado
        int primeiroUmEncontrado = 0;

        // Imprimir os números após o primeiro 1 até a mantissa
        int parte_inteira = (int)numeros_decimais;
        double parte_fracionaria = numeros_decimais - parte_inteira;
        while (parte_fracionaria > 0 && parteMantissa < mantissa) {
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;

            // Imprimir somente após o primeiro "1" ser encontrado
            if (primeiroUmEncontrado) {
                printf("%d", bit);
                parteMantissa++;
            }

            parte_fracionaria -= bit;

            // Marcar que o primeiro "1" foi encontrado após imprimir o primeiro "1"
            if (bit == 1) {
                primeiroUmEncontrado = 1;
            }
        }

        // Imprimir zeros para completar a mantissa se necessário
        while (parteMantissa < mantissa) {
            printf("0");
            parteMantissa++;
        }

        printf(" * 2^%d", expoente*(-1));

        if (expoente > maior_valor) {
            printf("  (UNDERFLOW) ");
        }
        if (expoente < menor_valor) {
            printf("  (OVERFLOW) ");
        }

        printf(" *Mantissa:%d", mantissa);
    }
}

void normalizar_binario_negativo_C1(double numeros_decimais, int posicaoPonto, int tamanho, int menor_valor, int maior_valor, int mantissa) {
    // Multiplicar números_decimais por -1
    numeros_decimais = numeros_decimais * -1;

    if (posicaoPonto != -1) {
        int casasDeslocadas = posicaoPonto;
        printf("\n- Numero normalizado negativo (C1): ");
        printf("1 ");

        // Preencher com zeros até a posição do primeiro 1
        int posicaoFinal = tamanho - posicaoPonto;
        for (int i = 0; i < posicaoFinal; i++) {
            printf("1 ");
        }

        // Colocar o 1 na posição do primeiro 1
        printf("0");

        int expoente;
        int parteMantissa = 0; // Variável para contar os bits impressos

        expoente = -casasDeslocadas;

        // Variável para marcar que o primeiro "1" foi encontrado
        int primeiroUmEncontrado = 0;

        // Imprimir os números após o primeiro 1 até a mantissa
        int parte_inteira = (int)numeros_decimais;
        double parte_fracionaria = numeros_decimais - parte_inteira;
        while (parte_fracionaria > 0 && parteMantissa < mantissa) {
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;

            // Imprimir somente após o primeiro "1" ser encontrado
            if (primeiroUmEncontrado) {
                if (bit == 0) {
                    printf("1");
                }
                else {
                    printf("0");
                }
                parteMantissa++;
            }

            parte_fracionaria -= bit;

            // Marcar que o primeiro "1" foi encontrado após imprimir o primeiro "1"
            if (bit == 1) {
                primeiroUmEncontrado = 1;
            }
        }

        // Imprimir zeros para completar a mantissa se necessário
        while (parteMantissa < mantissa) {
            printf("0");
            parteMantissa++;
        }

        printf(" * 2^%d", expoente*(-1));

        if (expoente > maior_valor) {
            printf("  (UNDERFLOW) ");
        }
        if (expoente < menor_valor) {
            printf("  (OVERFLOW) ");
        }

        printf(" *Mantissa:%d", mantissa);
    }
}

void normalizar_binario_negativo_C2(double numeros_decimais, int posicaoPonto, int tamanho, int menor_valor, int maior_valor, int mantissa) {
    // Multiplicar números_decimais por -1
    numeros_decimais = numeros_decimais * -1;

    if (posicaoPonto != -1) {
        int casasDeslocadas = posicaoPonto;
        printf("\n- Numero normalizado negativo (C2): ");
        printf("1 ");

        // Preencher com zeros até a posição do primeiro 1
        int posicaoFinal = tamanho - posicaoPonto;
        for (int i = 0; i < posicaoFinal; i++) {
            printf("1");
        }

        // Se o último bit for 0, imprimir 1
        printf("1");

        int expoente;
        int parteMantissa = 0; // Variável para contar os bits impressos

        expoente = -casasDeslocadas;

        // Variável para marcar que o primeiro "1" foi encontrado
        int primeiroUmEncontrado = 0;

        // Variável para marcar se houve overflow ou underflow
        int overflow = 0;
        int underflow = 0;

        // Imprimir os números após o primeiro 1 até a mantissa
        int parte_inteira = (int)numeros_decimais;
        double parte_fracionaria = numeros_decimais - parte_inteira;
        int ultimoBit = 0;
        while (parte_fracionaria > 0 && parteMantissa < mantissa) {
            parte_fracionaria *= 2;
            int bit = (int)parte_fracionaria;

            // Fazer a negação dos bits após o primeiro "1" ser encontrado
            if (primeiroUmEncontrado) {
                if (bit == 0) {
                    printf("1");
                    ultimoBit = 1;
                }
                else {
                    printf("0");
                    ultimoBit = 0;
                }
                parteMantissa++;
            }
            else {
                // Marcar que o primeiro "1" foi encontrado após imprimir o primeiro "1"
                if (bit == 1) {
                    primeiroUmEncontrado = 1;
                }
            }

            parte_fracionaria -= bit;

            // Verificar se houve overflow ou underflow
            if (expoente > maior_valor) {
                overflow = 1;
            }
            if (expoente < menor_valor) {
                underflow = 1;
            }
        }

        // Se o último bit for 0, imprimir 1
        if (ultimoBit == 0) {
            printf("1");
        }

        // Imprimir zeros para completar a mantissa se necessário
        while (parteMantissa < mantissa) {
            printf("0");
            parteMantissa++;
        }

        // Imprimir o expoente
        printf(" * 2^%d", expoente*(-1));

        if (expoente > maior_valor) {
            printf("  (UNDERFLOW) ");
        }
        if (expoente < menor_valor) {
            printf("  (OVERFLOW) ");
        }

        printf(" *Mantissa:%d", mantissa);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void normalizar_com_parte_inteira_negativa_SA(double numeros_decimais, int parte_inteira, int menor_valor, int maior_valor, int mantissa) {
    numeros_decimais *= -1;

    printf("\n- Numero normalizado negativo (SA): ");
    
    printf("1 ");
    // Converter a parte inteira para binário
    int binario_parte_inteira[64];
    int indice = 0;
    while (parte_inteira > 0) {
        binario_parte_inteira[indice++] = parte_inteira % 2; //pegar o resto
        parte_inteira /= 2; // dividir por 2
    }
    for (int i = indice - 1; i >= 0; i--) {
        printf("%d", binario_parte_inteira[i]);
    }

    // Normalizar o número com parte inteira
    double parte_fracionaria = numeros_decimais - (int)numeros_decimais;
    int parteMantissa = 0; // Variável para contar os bits impressos
    while (parte_fracionaria > 0 && parteMantissa < mantissa) {
        parte_fracionaria *= 2;
        int bit = (int)parte_fracionaria;
        parte_fracionaria -= bit;
        printf("%d", bit);
        parteMantissa++;
    }

    // Preencher com zeros para completar a mantissa se necessário
    while (parteMantissa < mantissa) {
        printf("0");
        parteMantissa++;
    }

    printf(" * 2^%d", indice);

    if (indice > maior_valor) {
        printf("  (OVERFLOW) ");
    }
    if (indice < menor_valor) {
        printf("  (UNDERFLOW) ");
    }

    printf(" *Mantissa:%d", mantissa);

    printf("\n");
}

void normalizar_com_parte_inteira_negativa_C1(double numeros_decimais, int parte_inteira, int menor_valor, int maior_valor, int mantissa) {
    numeros_decimais *= -1;

    printf("- Numero normalizado negativo (C1): ");
    
    printf("1 ");
    // Converter a parte inteira para binário
    int binario_parte_inteira[64];
    int indice = 0;
    while (parte_inteira > 0) {
        binario_parte_inteira[indice++] = parte_inteira % 2; //pegar o resto
        parte_inteira /= 2; // dividir por 2
    }
    
    for (int i = indice - 1; i >= 0; i--) {
        if (binario_parte_inteira[i] == 0) {
            printf("1");
        }
        else {
            printf("0");
        } 
    }

    // Normalizar o número com parte inteira
    double parte_fracionaria = numeros_decimais - (int)numeros_decimais;
    int parteMantissa = 0; // Variável para contar os bits impressos
    while (parte_fracionaria > 0 && parteMantissa < mantissa) {
        parte_fracionaria *= 2;
        int bit = (int)parte_fracionaria;
        parte_fracionaria -= bit;
        if (bit == 0) {
            printf("1");
        }
        else {
            printf("0");
        }
        parteMantissa++;
    }

    // Preencher com zeros para completar a mantissa se necessário
    while (parteMantissa < mantissa) {
        printf("0");
        parteMantissa++;
    }

    printf(" * 2^%d", indice);

    if (indice > maior_valor) {
        printf("  (OVERFLOW) ");
    }
    if (indice < menor_valor) {
        printf("  (UNDERFLOW) ");
    }

    printf(" *Mantissa:%d", mantissa);

    printf("\n");
}

void normalizar_com_parte_inteira_negativa_C2(double numeros_decimais, int parte_inteira, int menor_valor, int maior_valor, int mantissa) {
    numeros_decimais *= -1;
    numeros_decimais += 1;
    
    printf("- Numero normalizado negativo (C2): ");
    
    printf("1 ");
    // Converter a parte inteira para binário
    int binario_parte_inteira[64];
    int indice = 0;
    while (parte_inteira > 0) {
        binario_parte_inteira[indice++] = parte_inteira % 2; //pegar o resto
        parte_inteira /= 2; // dividir por 2
    }
    for (int i = indice - 1; i >= 0; i--) {
        if (binario_parte_inteira[i] == 0) {
            printf("1");
        }
        else {
            printf("0");
        }
    }

    // Normalizar o número com parte inteira
    double parte_fracionaria = numeros_decimais - (int)numeros_decimais;
    int contador_mantissa = 0; // Contador para a mantissa
    while (parte_fracionaria > 0 && contador_mantissa < mantissa) {
        parte_fracionaria *= 2;
        int bit = (int)parte_fracionaria;
        parte_fracionaria -= bit;
        if (bit == 0) {
            printf("1");
        }
        else {
            printf("0");
        }
        contador_mantissa++; // Incrementa o contador da mantissa
    }
    
    printf(" * 2^%d", indice);

    if (indice > maior_valor) {
        printf("  (OVERFLOW) ");
    }
    if (indice < menor_valor) {
        printf("  (UNDERFLOW) ");
    }

    printf(" *Mantissa:%d", mantissa);

    printf("\n");
}

//___________________________________NORMALIZAR BINARIO______________________________________________________________________

//__________________________________________MODIFICAR_________________________________________________________________________________

void modificar_valores(int indice) {
    printf("\nDigite o novo valor de menor_valor: ");
    scanf("%d", &valores_inseridos[indice].menor_valor);

    printf("\nDigite o novo valor de maior_valor: ");
    scanf("%d", &valores_inseridos[indice].maior_valor);
}

void modificar_numeros_decimais(int indice) {
    printf("\nDigite o novo valor em base decimal: ");
    scanf("%lf", &valores_inseridos[indice].numeros_decimais);
}

void modificar_todos_valores(int indice) {
    printf("\nDigite o novo valor de mantissa: ");
    scanf("%d", &valores_inseridos[indice].mantissa);

    printf("\nDigite o novo valor de menor_valor: ");
    scanf("%d", &valores_inseridos[indice].menor_valor);

    printf("\nDigite o novo valor de maior_valor: ");
    scanf("%d", &valores_inseridos[indice].maior_valor);

    printf("\nDigite o novo valor em base decimal: ");
    scanf("%lf", &valores_inseridos[indice].numeros_decimais);
}
    
//__________________________________________MODIFICAR________________________________________________________________________________
void loop_insercao() {
    struct Valores novo_valor;

    printf("Digite a Mantissa (n): ");
    scanf("%d", &novo_valor.mantissa);

    printf("Digite o Menor valor do expoente (l): ");
    scanf("%d", &novo_valor.menor_valor);

    printf("Digite o Maior valor do expoente (u): ");
    scanf("%d", &novo_valor.maior_valor);

    if (novo_valor.menor_valor > novo_valor.maior_valor) {
        printf("\nErro: O Menor valor do expoente (l) nao pode ser maior que o Maior valor do expoente (u).\n");
        return;
    }

    int continuar_insercao = 1;
    contador_valores = 0; // Zerar o contador de valores inseridos

    while (continuar_insercao) {
        printf("Digite o numero decimal (ou 0 para parar): ");
        scanf("%lf", &novo_valor.numeros_decimais);

        if (novo_valor.numeros_decimais == 0) {
            continuar_insercao = 0; // Se o usuário digitar 0, pare a inserção
        } else {
            valores_inseridos[contador_valores++] = novo_valor;
        }
    }

    j1:

    system("cls");

    // Dentro do loop que imprime a conversão de decimal para binário
    for (int i = 0; i < contador_valores; i++) {

        printf("\n");
        printf("\n%d) Mantissa: %d\n   Menor valor do expoente: %d\n   Maior valor do expoente: %d\n   Numeros em base decimal: %lf\n\n",
            i + 1, valores_inseridos[i].mantissa, valores_inseridos[i].menor_valor,
            valores_inseridos[i].maior_valor, valores_inseridos[i].numeros_decimais);

        if (valores_inseridos[i].numeros_decimais < 0) {
            printf("\n\n- Numero negativo convertido de binario para decimal: ");
            binario_decimal_negativo(valores_inseridos[i].numeros_decimais);
        }
        else {
            printf("- Numero convertido de decimal para binario: ");
            decimal_binario(valores_inseridos[i].numeros_decimais);

            printf("\n- Numero convertido de binario para decimal: ");
            binario_decimal(valores_inseridos[i].numeros_decimais);
        }
        
        int parte_inteira = (int)valores_inseridos[i].numeros_decimais;
        if (parte_inteira == 0) {
            int posicaoPonto = 0;
            int tamanho = contar_binario(valores_inseridos[i].numeros_decimais, &posicaoPonto);

            // Normalizar o número binário
            if (valores_inseridos[i].numeros_decimais < 0) {
                normalizar_binario_negativo_SA(valores_inseridos[i].numeros_decimais, posicaoPonto, tamanho, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
                normalizar_binario_negativo_C1(valores_inseridos[i].numeros_decimais, posicaoPonto, tamanho, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
                normalizar_binario_negativo_C2(valores_inseridos[i].numeros_decimais, posicaoPonto, tamanho, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
            }
            else {
                normalizar_binario(valores_inseridos[i].numeros_decimais, posicaoPonto, tamanho, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
            }
            
        } else {
            if (valores_inseridos[i].numeros_decimais > 0) {
                normalizar_com_parte_inteira(valores_inseridos[i].numeros_decimais, parte_inteira, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
            }
            else {
                parte_inteira *= -1;
                normalizar_com_parte_inteira_negativa_SA(valores_inseridos[i].numeros_decimais, parte_inteira, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
                normalizar_com_parte_inteira_negativa_C1(valores_inseridos[i].numeros_decimais, parte_inteira, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
                parte_inteira -= 1;
                normalizar_com_parte_inteira_negativa_C2(valores_inseridos[i].numeros_decimais, parte_inteira, valores_inseridos[i].menor_valor, valores_inseridos[i].maior_valor, valores_inseridos[i].mantissa);
            }
            
        }
    }

    printf("\n");

    printf("\nEscolha uma opcao:\n");
    printf("1) Modificar valores\n");
    printf("2) Adicionar novos valores\n");
    printf("0) Sair\n");

    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            printf("\nEscolha qual modificar: ");
            int entrada_modificar;
            scanf("%d", &entrada_modificar);

            while (entrada_modificar > 0 && entrada_modificar <= contador_valores) {
                printf("\nEscolha uma opcao:\n");
                printf("1) Modificar menor_valor e maior_valor\n");
                printf("2) Modificar numeros_decimais\n");
                printf("3) Modificar todos os valores\n");
                printf("0) Sair\n");

                int opcao_modificar;
                scanf("%d", &opcao_modificar);

                switch (opcao_modificar) {
                    case 1:
                        modificar_valores(entrada_modificar - 1);
                        goto j1;
                        break;
                    case 2:
                        modificar_numeros_decimais(entrada_modificar - 1);
                        goto j1;
                        break;
                    case 3:
                        modificar_todos_valores(entrada_modificar - 1);
                        goto j1;
                        break;
                    case 0:
                        break;
                    default:
                        printf("\nOpcao invalida.\n");
                        break;
                }

                system("cls");

                printf("\n");

                for (int i = 0; i < contador_valores; i++) {
                    printf("\n%d) Mantissa(n): %d\n   Menor valor do expoente(l): %d\n   Maior valor do expoente(l): %d\n   Numeros em base decimal: %lf\n\n",
                        i + 1, valores_inseridos[i].mantissa, valores_inseridos[i].menor_valor,
                        valores_inseridos[i].maior_valor, valores_inseridos[i].numeros_decimais);
                    printf("- Novo numero %.10lf em binario: ", valores_inseridos[i].numeros_decimais);
                    decimal_binario(valores_inseridos[i].numeros_decimais);
                    printf("\n");
                }

                printf("\nDigite o numero da entrada que deseja modificar (0 para sair): ");
                scanf("%d", &entrada_modificar);
            }
            break;
        }
        case 2:
            loop_insercao();
            break;
        case 0:
            break;
        default:
            printf("\nOpcao invalida.\n");
            break;  
    }
}

int main() {  
    loop_insercao();    
}