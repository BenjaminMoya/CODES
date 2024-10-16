import { useEffect, useState } from "react"

const userList = () => {

    const [users,setUsers] = useState([]);//Hook que define variables de estado

    const navigate = useNavigate();

    const init = () => {
        userService
            .getAll()
            .then((response) => {
                console.log("Lista de usuarios",response.data);
                setUsers(response.data);
            })
            .catch((error) => {
                console.log("Error:",error);
            });

    }

    useEffect() //Para cambiar el css por cada rol que ocupe la web

    const handle = (variable) => {

        variable.preventDefault();//Para evitar el refreco automatico
        const confirmation= window.confirm{
            "..."
        };
        if(confirmation){
            //...
            navigate("...");//Rutea servicios
        }

    }
    
    return{
        //Html <TableBody> para mostrar una tabla
        //users.map ((user) => ...) como un for each 
    }
}