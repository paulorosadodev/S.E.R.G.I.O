import serial
import os
os.system('cls')

dados = serial.Serial("COM8", 9600)

lista = []
while True:
    if dados.in_waiting:
        data = dados.readline().decode()
        if "ALERTA" in data:
            print(data.strip())
            pass
        else:
            lista.append(float(data))
            consumo_total = sum(lista)
            conta = consumo_total * 0.25
            print(f"A consumo do mes foi de {consumo_total:.2f} L, totalizando R${conta:.2f}")
