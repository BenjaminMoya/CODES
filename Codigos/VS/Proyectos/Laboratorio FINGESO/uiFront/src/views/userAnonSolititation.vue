<template>
    <div class="main">
        <header>
            <div class="container1">
                <h1 class="alineacion">InstaHome</h1>
                <router-link to="/login">
                    <div type="button" class="btn btn-primary">Iniciar sesion</div>
                </router-link>
            </div>
            
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container-fluid">
                    <a class="navbar-brand" href="#">
                    <img src="./media/logo1.jpg" alt="" width="30" height="24"> </img>
                    </a>
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
                            <li class="nav-item">
                                <a class="nav-link active" aria-current="page" href="#">Home</a>
                            </li>
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
                            <li class="nav-item">
                                <a class="nav-link disabled" href="#" tabindex="-1" aria-disabled="true">Disabled</a>
                            </li>
                        </ul>
                        <form class="d-flex">
                            <input class="form-control me-2" type="search" placeholder="Search" aria-label="Search">
                            <button class="btn btn-outline-success" type="submit">Search</button>
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
                    <div class="card-content">
                        <h3 class="letter">Propiedad 1</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 2</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
                <div class="card">
                    <div class="card-content">
                        <h3 class="letter">Propiedad 3</h3>
                        <p class="letter">Descripcion de la propiedad:"Texto de ejemplo"</p>
                        <p class="letter">Valor:"Texto de ejemplo"</p>
                        <button>Ver mas</button>
                    </div>
                </div>
            </div>
        </section>   
    </div>
</template>

<script>


</script>


<style>
.main{

    background-image: url('./media/usach.jpg'); /* Ruta a tu imagen de fondo */
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

.card{

    box-sizing: border-box;
    background-color: #f8f6f691;

}
.alineacion{

    color: black;
    text-align: left;
}
</style>