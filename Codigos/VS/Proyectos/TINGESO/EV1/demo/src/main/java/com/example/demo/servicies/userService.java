package com.example.demo.servicies;

import com.example.demo.entities.userEntity;
import com.example.demo.repositories.userRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;

@Service
public class userService {

    @Autowired
    userRepository UserRepository;

    public ArrayList<userEntity> getUsers(){
        return (ArrayList<userEntity>) UserRepository.findAll();
    }

    public userEntity saveUser(userEntity newUser){

        userEntity userTemp = getUserByRut(newUser.getUserRut());
        if(userTemp != null){

            return null;
        }

        return UserRepository.save(newUser);
    }

    public int login (String userEmail, String userPassword){

        userEntity userTemp = getUserByEmail(userEmail);
        if(userTemp != null){

            if(userPassword.equals(userTemp.getUserPassword())){

                return 1;
            }
        }
        return 0;
    }

    public userEntity getUserById(Long userId){
        return UserRepository.findByUserId(userId);
    }

    public userEntity getUserByRut(String userRut){
        return UserRepository.findByUserRut(userRut);
    }

    public userEntity getUserByEmail(String userEmail){
        return UserRepository.findByUserEmail(userEmail);
    }

    public userEntity updateUser(userEntity user) {
        return UserRepository.save(user);
    }

    public boolean deleteUser(Long userId) throws Exception {
        try{
            UserRepository.deleteById(userId);
            return true;
        } catch (Exception e) {
            throw new Exception(e.getMessage());
        }
    }

}