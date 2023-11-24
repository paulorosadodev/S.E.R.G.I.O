# S.E.R.G.I.O (Sistema Eletrônico de Registro de Gerenciamento Inteligente de h2O) 
Um **hidrômetro inteligente** que envia por Bluetooth os dados de consumo de água e uma mensagem de alerta caso o dispositivo sofra alguma movimentação suspeita.

![IMG_1707](https://github.com/paulorosadodev/S.E.R.G.I.O/assets/117609505/33ba2331-3c48-47b0-b4be-d32eba40c084)

O S.E.R.G.I.O foi desenvolvido com o objetivo de solucionar a questão do **furto de hidrômetros na Região Metropolitana do Recife**, sem a necessidade de um funcionário ir pessoalmente ao equipamento para registrar o valor lido, vai ser possível colocá-lo em um local mais seguro e protegido, diminuindo o número de furtos.
## ⚡ Componentes Internos:
![image](https://github.com/paulorosadodev/S.E.R.G.I.O/assets/117609505/e130db2c-8909-443e-aa6f-c4fed8746e83)
* 1x Arduino UNO;
* 1x Protoboard;
* 1x Resistor 220 ohms;
* 16x jumpers;
* 1x Bateria 9v;
* 1x Adaptador para bateria 9v com plug;
* 1x LED para identificar o estado do dispositivo;
* 1x Sensor de Fluxo YS-F201 para medir o consumo de água em litros;
* 1x Acelerômetro MPU6050 para detectar se houve alguma movimentação suspeita;
* 1x Módulo Bluetooth HC-05 para enviar os dados para um monitor serial em outro dispositivo.
## 🚨 Como interpretar a LED:
### 1️⃣ Funcionamento padrão do dispositivo:
<div align="center">
  <img width="tamanho da imagem" title="titulo da imagem" src="https://github.com/paulorosadodev/S.E.R.G.I.O/assets/117609505/8134d21d-55a2-4d3c-872c-0b32fe4ddd04"/>
  
  Enquanto não estiver detectando fluxo ou movimentação suspeita, a LED piscará em um intervalo de 1 segundo.
</div>

### 2️⃣ Fluxo de água detectado:
<div align="center">
  <img width="tamanho da imagem" title="titulo da imagem" src="https://github.com/paulorosadodev/S.E.R.G.I.O/assets/117609505/973bf759-6aa2-4681-9413-3494dad4d01e"/>

  Enquanto for detectado fluxo de água, a LED permanecerá acesa.
</div>

### 3️⃣ Movimentação suspeita detectada:
<div align="center">
  <img width="tamanho da imagem" title="titulo da imagem" src="https://github.com/paulorosadodev/S.E.R.G.I.O/assets/117609505/a4926d2b-6246-40c3-9a75-ec98d3780d52"/>

  Se uma movimentação suspeita for detectada, a LED piscará em um intervalo de 1/2 segundo.
</div>

🔗 [Saiba mais sobre nosso projeto](https://sites.google.com/cesar.school/jedis-g10/)

Desenvolvido por: **Beatriz Pereira**, **Érico Chen**, **Daniel Barreto**, **Did Silveira**, **Felipe Caminha**, **Gabriel Tabosa**, **João Victor Nunes**, **Marina Machado**, **Paulo Rosado**, **Pedro Dhalia** e **Raul Luna**.

*Projeto desenvolvido para a disciplina de Projetos 1 dos cursos de Design e Ciência da Computação na CESAR School*
