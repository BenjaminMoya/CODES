<script setup>

</script>

<template>
    <main>
        <div class="general">
            <div class="content">
                <img class="image" src="./media/usach2.png">
                <div class="header">Inicio de sesion</div>
                <div class="headerDescription" v-if="!register">Completar campos para iniciar sesion</div>
                <div class="headerDescription" v-else>Completar campos para registro</div>
                <div class="inputContainer" v-if="!register">
                    <input type="email" v-model="username" placeholder="Ingrese correo">
                    <input type="password" v-model="password" placeholder="Ingrese contraseña">
                    <button class="sessionButton" @click="login">Iniciar sesion</button>
                </div>
                <div class="inputContainer" v-else>
                    <input type="email" v-model="usernameRegister" placeholder="Ingrese correo">
                    <input type="password" v-model="passwordRegister" placeholder="Ingrese contraseña">
                    <input type="password" v-model="passwordRegisterConfirmation" placeholder="Repita contraseña">
                    <button class="sessionButton" @click="add">Registrar</button>
                </div>
                <div class="alsoButtons"> // aqui se maneja en el login si quieres iniciar sesion o quieres registarte
                    <div class="alsoButton" @click="handleChanger" v-if="!register">Registrarse</div>
                    <div class="alsoButton" @click="handleChanger" v-else>Iniciar sesion</div>
                    <router-link to="/">
                        <div class="alsoButton" @click="handleChanger">Ingreso anonimo</div>
                    </router-link>
                </div>
            </div>
        </div>
    </main>
</template>

<script> 
import axios from 'axios'

//Funciones de Redireccionamiento a vistas. lo ideal es que estas se dentro de los metodos declarados debajo :p
function redirectUserLogin(){

    window.location.href = '/user';
}

function redirectUserAnon(){

    window.location.href = '/';
}

export default{ // me sale error pero no cache como solucionarlo....

    data(){

        return{//datos predeterminados
            username: '',
            password: '',
            logged: false,
            register: false,
            usernameRegister: '',
            passwordRegister: '',
            passwordRegisterConfirmation: '',

        }
    },

    methods:{

        async login(){

            //envio de datos al backend los cuales tienen que tener los mismos identificadores
            const user = {

                "email":this.username,
                "password":this.password,

            };
            try{

                const respuesta = await axios.post(import.meta.env.VITE_BASE_URL + "api/user/login",user);//enviando los datos al back y esperando una conexion. si no conecta lo
                //mas seguro es que este mal el puerto,la variable de entorno o la ruta asi que revisar bien....

                //tipos de usuario
                if(respuesta.data == 1){

                    return 0;
                }
                if(respuesta.data == 2){

                    return 0;
                }
                if(respuesta.data == 3){

                    localStorage.setItem("login",JSON.stringify(this.username));//guardando datos en el navegador
                    redirectUserLogin();//redireccionar a la vista del usuario en la pagina principal
                }
                if(respuesta.data == 0){

                    alert("Credenciales invalidas");
                }
                respuesta.data = 0;
                console.log(respuesta.data);
            } catch (error) {

                alert("Fallo en la conexion con el servidor");//aqui uno se da cuenta si axio fallo

            }
        },
        handleChanger(){

            this.register = !this.register;
            console.log(this.register);
        },
        anon(){

            this.username= "anon";
            redirectUserAnon();//redireccionar a la pagina pricnipal como anonimo, osea simplemente no hace nada ajskajksas :p
            localStorage.setItem("login",JSON.stringify(this.username))

        },
        async addUser(){//registro de usuario

            if(this.usernameRegister!= " " && this.passwordRegisterConfirmation!=" "){
                if(this.passwordRegister == this.passwordRegisterConfirmation){

                    const new_user = {

                        "email":this.usernameRegister,
                        "password":this.passwordRegister,
                        "rol": "user",
                    }
                    try{
                        const registro = await axios.post(import.meta.env.VITE_BASE_URL + "api/user/register",new_user); //guardando datos en el back
                        console.log(registro);
                        alert("Usuario creado con exito");
                    } catch(error){

                        alert("El usuario no se pudo registrar");//si es que no hubo conexion se da el aviso
                    }
                } else {

                    alert("Las contraseñas no coinciden");
                }
            } else {

                alert("Rellene todos los campos para registrarse");
            }
        }
    }
}
</script>

<style scoped>
.general{

    background-image: url("./media/usach.jpg");

    height: 100vh;
    background-repeat: no-repeat;
    background-size: cover;
    background-position: center;

    display: flex;
    justify-content: center;
    align-items: center;
    align-content: center;
}
.sessionButton{

    height: 30px;
    background-color: #1769aa;
    color: #f5f5f5;
    font-size: 16px;
    font-weight: 500;
    border: #1769aa solid 2px;
    border-radius: 3px;
    cursor: pointer;
    transition: background-color 0.2s;
    margin-bottom: 10px;
}

.sessionButton:hover{
    background-color: #4f8dbe;
    transition: background-color 0.2s;

}
.image{

    height: 150px;
}

.content{

    box-sizing: border-box;
    padding: 10px;
    background-color: #f8f6f6f3;
    display: flex;
    flex-direction: column;
    align-items: center;

    min-width: 300px;
    max-width: 500px;
    width: 100%;
    margin: 0px 10px 0px 10px;
    min-height: 500px;
    max-height: 550px;
    height: 100%;

    border-radius: 10px;
}

.header{
    text-align: center;
    line-height: 1;
    font-size: 40px;
    font-weight: 500 !important;
    color: black;
}

.headerDescription{

    font-size: 16px;
    margin-bottom: 20px;
    color: black;
}

.inputContainer{
    display: flex;
    gap: 1px;
    width: 100%;
    max-width: 400px;
    flex-direction: column;

}

.input{

    height: 50px;
    box-sizing: border-box;

    padding: 10px !important;
    font-size: 16px;
    border-radius: 4px;
    outline: none;
    border: #cdcdcd solid 3px;
    transition: border 0.2s;
}
.input:hover{
    border: #bbbbbb solid 3px;
    transition: border 0.2s;

}
.input:focus{
    border: #888888 solid 3px;
    transition: border 0.2s;
}

.alsoButton{
    
    text-align: center;
    cursor: pointer;
    font-weight: 500;
    transition: all 0.2s;
    color: black;

}

.alsoButton:hover{

    text-decoration: underline;
    transition: all 0.2s;
}
@media(min-width: 418px){

    .content{
        max-height: 500px;
    }
}
</style>