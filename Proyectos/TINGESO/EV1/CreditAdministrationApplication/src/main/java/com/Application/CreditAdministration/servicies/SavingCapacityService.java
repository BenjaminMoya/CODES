package com.Application.CreditAdministration.servicies;

import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class SavingCapacityService {

    @Autowired
    UserService userService;

    @Autowired
    UserRepository userRepository;

    public int minAmount(long userId,double creditAmount){
        UserEntity user = userRepository.findByUserId(userId);
        if(creditAmount*0.1 < user.getUserBalance()){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            userService.updateUser(user);
            return 1;
        } else {
            return 0;
        }
    }

    public int savingHistory(long userId,boolean greatRetirement){
        if(greatRetirement){
            return 0;
        }
        UserEntity user = userRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        userService.updateUser(user);
        return 1;
    }

    public int periodicDeposit(long userId, double monthlyDeposit, double monthlyEntry, boolean isPeriodic){

        if(!isPeriodic) {
            return 0;
        }

        if(monthlyDeposit < monthlyEntry*0.05){
            return 0;
        }

        UserEntity user = userRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        userService.updateUser(user);
        return 1;
    }

    public int relationSA(long userId, double creditAmount){
        UserEntity user = userRepository.findByUserId(userId);

        if(user.getUserAccountSeniority() < 2 && user.getUserBalance() >= creditAmount*0.2){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            userService.updateUser(user);
            return 1;
        }

        if(user.getUserAccountSeniority() >= 2 && user.getUserBalance() >= creditAmount*0.1){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            userService.updateUser(user);
            return 1;
        }

        return 0;
    }

    public int recentOut(long userId, double maxRetirement){

        UserEntity user = userRepository.findByUserId(userId);
        if(user.getUserBalance()*0.3 < maxRetirement){
            return 0;
        }
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        userService.updateUser(user);
        return 1;
    }

}
