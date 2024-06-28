<script setup>
  import {ref} from 'vue'
  const name = 'vue 3';
  const styleColor = "color: rgb(0, 181, 194);";
  const array = ["😀", "🤠", "☠️", "🦧", "🦦"];
  const array2 = [
      {
          name: "Manzana",
          price: "1.00",
          description: "Una manzana",
          stock: 0,
      },
      {
          name: "Pera",
          price: "2.00",
          description: "Una pera",
          stock: 20,
      },
      {
          name: "Naranja",
          price: "3.00",
          description: "Una naranja",
          stock: 30
      },
  ];
  const activo = true;
  const counter = ref(0);
  //funciones
  const handleClick = () =>{

    console.log("Gei el que lea")
  } 
  const increment = () =>{

    counter.value++;
  }
  const decrement = () =>{

  counter.value--;
  }
  const reset = () =>{

  counter.value = 0;
  }
</script>

<template>
    <h1> Hola {{name.toUpperCase()}}! </h1> <br>
    <h2 :style = "styleColor"> Bienvenido a Vue 3 </h2> <br>
    <p v-if = "activo"> Estoy activo </p> 
    <p v-else> Estoy Inactivo </p> <br>
    <ul>
      <li
        v-for="(emoji,index) in array"
        :key = "index"
      > {{ index }} : {{emoji}}
    </li>
    </ul>

    <ul>
        <template 
          v-for="(fruta,index) in array2"
          :key = "index">
            <li 
            v-if = "fruta.stock > 0">
            {{ index + 1 }}: 
            <ul> 
              <li v-for = "info in fruta">
                {{info}} 
             </li>
            </ul>
            </li> 
        </template>
    </ul> <br>

    <button v-on:click.rigth = "handleClick"> Click! 1 </button> <br>
    <button @click = "handleClick"> Click! 2</button> <br>
    <button @click.middle = "handleClick"> Click! 3</button> <br>
    <button @click = "increment"> Aumentar el contador</button> <br>
    <button @click = "decrement"> Disminuir el contador</button> <br>
    <button @click = "reset"> Resetear el contador</button> <br>
    <h2 :class="counter > 0 ? 'positive' : 'negative' " > {{counter}} </h2>
</template>

<style>
    h1 {
        color: rgb(0, 181, 194);
    }
    .positive{
        color: green;
    }
    .negative{
        color: red;
    }
</style>