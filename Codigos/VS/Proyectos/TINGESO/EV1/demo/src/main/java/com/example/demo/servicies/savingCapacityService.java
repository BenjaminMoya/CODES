package com.example.demo.servicies;

import com.example.demo.entities.userEntity;
import com.example.demo.repositories.userRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;

@Service
public class savingCapacityService {

    @Autowired
    userService UserService;

    @Autowired
    userRepository UserRepository;

    public int minAmount(long userId,double creditAmount){
        userEntity user = UserRepository.findByUserId(userId);
        if(creditAmount*0.1 < user.getUserBalance()){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            UserService.updateUser(user);
            return 1;
        } else {
            return 0;
        }
    }

    public int savingHistory(long userId,boolean greatRetirement){
        if(greatRetirement){
            return 0;
        }
        userEntity user = UserRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

    public int periodicDeposit(long userId, double monthlyDeposit, double monthlyEntry, boolean isPeriodic){

        if(!isPeriodic) {
            return 0;
        }

        if(monthlyDeposit < monthlyEntry*0.05){
            return 0;
        }

        userEntity user = UserRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

    public int relationSA(long userId, double creditAmount){
        userEntity user = UserRepository.findByUserId(userId);

        if(user.getUserAccountSeniority() < 2 && user.getUserBalance() >= creditAmount*0.2){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            UserService.updateUser(user);
            return 1;
        }

        if(user.getUserAccountSeniority() >= 2 && user.getUserBalance() >= creditAmount*0.1){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            UserService.updateUser(user);
            return 1;
        }

        return 0;
    }

    public int recentOut(long userId, double maxRetirement){

        userEntity user = UserRepository.findByUserId(userId);
        if(user.getUserBalance()*0.3 < maxRetirement){
            return 0;
        }
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

}
