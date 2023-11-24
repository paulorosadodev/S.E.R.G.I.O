#Importa as bibliotecas "serial" e "os"
import serial
import os

os.system('cls') #Limpa o terminal

lista = []

dados = serial.Serial("COM8", 9600) # Armazena a informação recebida pelo Arduino na variável dados
 
while True:
    if dados.in_waiting:
        data = dados.readline().decode() # Tratamento dos dados
        if "ALERTA" in data:
            print(data.strip()) # Printa o alerta de movimentação suspeita
            pass
        else:
            lista.append(float(data)) 
            consumo_total = sum(lista)
            conta = consumo_total * 0.25 # Calcula o valor da conta através do consumo total
            print(f"A consumo do dia foi de {consumo_total:.2f} L, totalizando R${conta:.2f}") # Printa o consumo em L e o valor da conta em R$
