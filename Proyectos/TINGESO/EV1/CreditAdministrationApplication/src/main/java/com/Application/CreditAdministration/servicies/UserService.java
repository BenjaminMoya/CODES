package com.Application.CreditAdministration.servicies;

import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.repositories.CreditRepository;
import com.Application.CreditAdministration.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class UserService {

    @Autowired
    UserRepository userRepository;

    @Autowired
    CreditRepository creditRepository;

    public List<UserEntity> getUsers(){
        return userRepository.findAll();
    }

    public UserEntity saveUser(UserEntity newUser){

        UserEntity userTemp = getUserByRut(newUser.getUserRut());
        if(userTemp != null){

            return null;
        }

        return userRepository.save(newUser);
    }

    public UserEntity login (String userEmail, String userPassword){

        UserEntity userTemp = getUserByEmail(userEmail);
        if(userTemp != null){

            if(userPassword.equals(userTemp.getUserPassword())){

                return userTemp;
            }
        }
        return null;
    }

    public UserEntity getUserById(Long userId){
        return userRepository.findByUserId(userId);
    }

    public UserEntity getUserByRut(String userRut){
        return userRepository.findByUserRut(userRut);
    }

    public UserEntity getUserByEmail(String userEmail){
        return userRepository.findByUserEmail(userEmail);
    }

    public UserEntity updateUser(UserEntity user) {
        return userRepository.save(user);
    }

    public int deleteUser(Long userId) throws Exception {
        try{
            userRepository.deleteById(userId);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    public int zeroSaving(Long userId){
        UserEntity userTemp = userRepository.findByUserId(userId);
        userTemp.setUserSavingCapacity(0);
        try{
            updateUser(userTemp);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    public double transferAmount(Long userId,Long creditId){
        UserEntity userTemp = userRepository.findByUserId(userId);
        CreditEntity creditTemp = creditRepository.findByCreditId(creditId);
        double amount = userTemp.getUserBalance()+creditTemp.getCreditRequestedAmount();
        userTemp.setUserBalance(amount);
        try{
            updateUser(userTemp);
            return amount;
        } catch (Exception e) {
            return 0;
        }
    }

}