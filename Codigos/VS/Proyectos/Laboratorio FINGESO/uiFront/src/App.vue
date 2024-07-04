<script setup>
  import {ref,  computed} from 'vue'
  let cond1 = true;
  let cond2 = false;
  const result = ref(0);
  const resultstr = ref("");

  const plus = () => {

    if(resultstr.value == ""){
      return;
    }
    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + " + ";
  }
  const minus = () => {
    if(resultstr.value == ""){
      return;
    }
    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + " - ";
  }
  const mult = () => {
    if(resultstr.value == ""){
      return;
    }
    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + " * ";
  }
  const div = () => {
    if(resultstr.value == ""){
      return;
    }
    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + " / ";
  }

  const eq = () => {

    cond1 = true;
    cond2 = false;
    result.value = result.value + eval(resultstr);
    resultstr.value = "";
    resultstr.value = resultstr.value + result.value.toString();
  }

  const clean = () => {

    result.value = 0;
    resultstr.value = "";
    cond1 = true;
    cond1 = false;
  }

  const one = () => {
    
    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "1"
  }
  const two = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "2"
  }
  const three = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "3"
  }
  const four = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "4"
  }
  const five = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "5"
  }
  const six = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "6"
  }
  const seven = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "7"
  }
  const eigth = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "8"
  }
  const nine = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "9"
  }
  const zero = () => {

    if(cond1){
      cond1 = false;
      cond2 = true;
    }
    resultstr.value = resultstr.value + "0"
  }

</script>

<template>
  <div class="container text-center mt-3">
    <h2> Calculadora </h2> <br>
    <!--
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
    -->
    <h2 v-if="cond1" > {{result}} </h2> 
    <h2 v-if="cond2" > {{resultsrt}} </h2> <br>
    <div class="btn-group">
      <button @click = "one" class="btn btn-secondary"> 1 </button> 
      <button @click = "two" class="btn btn-secondary"> 2 </button> 
      <button @click = "three" class="btn btn-secondary"> 3 </button> 
      <button @click = "plus" class="btn btn-primary"> + </button>
    </div><br>
    <div class="btn-group">
      <button @click = "four" class="btn btn-secondary"> 4 </button> 
      <button @click = "five" class="btn btn-secondary"> 5 </button> 
      <button @click = "six" class="btn btn-secondary"> 6 </button> 
      <button @click = "minus" class="btn btn-primary"> - </button>
    </div> <br>
    <div class="btn-group">
      <button @click = "seven" class="btn btn-secondary"> 7 </button> 
      <button @click = "eigth" class="btn btn-secondary"> 8 </button> 
      <button @click = "nine" class="btn btn-secondary"> 9 </button> 
      <button @click = "mult" class="btn btn-primary"> * </button>
    </div><br>
    <div class="btn-group">
      <button @click = "zero" class="btn btn-secondary"> 0 </button> 
      <button @click = "div" class="btn btn-primary"> / </button> 
      <button @click = "eq" class="resultado"> = </button> 
      <button @click = "clean" class="btn btn-danger"> C </button> 
    </div><br>

  </div> 
</template>

<style>
    h1 {
        color: rgb(0, 181, 194);
    }
    .resultado{
        color: green;
    }
    .error{
        color: red;
    }
    .zero{
        color: peru;
    }
</style>