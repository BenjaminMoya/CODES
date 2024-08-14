<template>
    <div class="container main">
        <header>
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container-fluid">
                    <a class="navbar-brand" href="#">
                        <h1 class="alineacion">InstaHome</h1>
                    </a>
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
                            <li class="nav-item">
                                <a class="nav-link" href="#">Link</a>
                            </li>
                            <li class="nav-item dropdown">
                                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false">
                                Dropdown
                                </a>
                                <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                                    <li><a class="dropdown-item" href="#">Action</a></li>
                                    <li><a class="dropdown-item" href="#">Another action</a></li>
                                    <li><hr class="dropdown-divider"></li>
                                    <li><a class="dropdown-item" href="#">Something else here</a></li>
                                </ul>
                            </li>
                        </ul>
                        <form class="d-flex">
                            <input class="form-control me-2" type="search" placeholder="Search" aria-label="Search">
                            <router-link to="/login">
                                <div type="button" class="btn btn-primary">Login</div>
                            </router-link>
                        </form>
                    </div>
                </div>
            </nav>
        </header>

        <section>
            <h1 class="letter">Propiedades Ideales</h1>
            <p class="letter">Explora las propiedades ideales que hay para ti</p>
        </section>

        <section id="properties">
            <h1 class="letter">Propiedades Disponibles</h1>
            <div class="card-container">
                <div class="card">
                    <img src="./media/casa1.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 1</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <img src="./media/casa6.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 2</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <img src="./media/casa3.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 3</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
            </div>
            <div class="card-container">
                <div class="card">
                    <img src="./media/casa3.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 4</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <img src="./media/casa5.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 5</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <img src="./media/casa6.jpg" alt="Imagen de la propiedad">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 6</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
            </div>
        </section>
        <footer class="pie">
            <p>&copy; 2024 Portal de arriendo.Todos los derechos reservados</p>
            <p><a href="#contact">Contactanos</a> para mas informacion</p>
        </footer> 
    </div>
</template>

<script>


</script>


<style>
.main{

    background: linear-gradient(45deg, #ffffff, #ffb6c1, #00aaff, #800080);
    background-size: cover;
    background-position: center;
    background-repeat: no-repeat;
    padding: 20px;
}

.card{

    background-color: transparent;
}

.letter{

    color: rgb(0, 0, 0);
}

.container1 {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.container1 p {
    margin: 0; 
}

.card-container{
    display: flex;
    justify-content: space-between;
    margin: 20px;
}
.card{

    background-color: #f8f6f691;
    border: 1px solid #ccc;
    border-radius: 8px;
    box-shadow: 0 4px 8px rgba(0,0,0,0.1);
    margin: 20px;
    max-width: 450px;
    overflow: hidden;
    transition: transform 0.3s;

}

.card:hover{
    transform: scale(1.1);
}

.card img{

    border-radius: 8px 8px 0 0;
    max-width: 100%;
    height: auto;
}

.card-content{

    color: black;
    padding: 15px;
}

.card-content h3{

    font-size: 1.5em;
    margin: 0.5em 0;
}

.card-content button{

    background-color: #007bff;
    border: none;
    border-radius: 4px;
    color: white;
    cursor: pointer;
    padding: 10px;
    width: 100%;
}

.card-content button:hover{

    background-color: #0056b3;
}

.navbar {
    padding-top: 5px;
    padding-bottom: 5px;
}

.navbar-brand h1 {
    font-size: 1.5rem;
    margin: 0;
}

.form-control {
    height: 38px; /* Asegúrate de que la altura sea la misma para el input */
    padding: 5px 10px;
    font-size: 1rem;
    border-radius: 5px; /* Si quieres que los bordes sean redondeados, iguala este valor */
}

.btn {
    height: 38px; /* Coincide la altura con la del input */
    padding: 5px 10px; /* Ajusta el padding si es necesario */
    font-size: 1rem; /* Coincide el tamaño de la fuente */
    line-height: 1.5; /* Asegura que el texto esté centrado */
    border-radius: 5px; /* Asegura que los bordes del botón sean similares al input */
    display: inline-flex; /* Asegura que el contenido interno se alinee correctamente */
    align-items: center; /* Centra el contenido verticalmente */
}

.navbar-nav .nav-item {
    margin-bottom: 0;
}
.alineacion{

    color: black;
    text-align: left;
    font-size: 100%;
}
.pie{

    text-align: center;
    padding: 10px; /* Añade algo de padding para separar el contenido del borde del footer */
    width: 100%;
    color:black;
}
</style>