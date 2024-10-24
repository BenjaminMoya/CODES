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

    public userEntity login (String userEmail, String userPassword){

        userEntity userTemp = getUserByEmail(userEmail);
        if(userTemp != null){

            if(userPassword.equals(userTemp.getUserPassword())){

                return userTemp;
            }
        }
        return null;
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

    public int zeroSaving(Long userId){
        userEntity userTemp = UserRepository.findByUserId(userId);
        userTemp.setUserSavingCapacity(0);
        try{
            updateUser(userTemp);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

}