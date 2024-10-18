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

    public int savingHistory(long userId,ArrayList<Double> monthlyBalance,ArrayList<Double> monthlyMaxOut){
        boolean noZero = true;
        for (Double amount : monthlyBalance) {
            if (amount<= 0) {
                noZero = false;
                break;
            }
        }

        for(int i = 0;i<monthlyMaxOut.size();i++){

            if(monthlyMaxOut.get(i)>(monthlyBalance.get(i)*0.5) || !noZero){
                return 0;
            }
        }

        userEntity user = UserRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

    public int periodicDeposit(long userId, ArrayList<Double> userDeposit, double monthlyEntry, boolean isPeriodic){

        if(!isPeriodic){
            return 0;
        }

        double monthlySum = 0;
        for(Double amount : userDeposit){
            monthlySum+=amount;
        }

        if(monthlySum < monthlyEntry*0.05){
            return 0;
        }

        userEntity user = UserRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

    public int relationSA(long userId, double creditAmount){
        userEntity user = UserRepository.findByUserId(userId);

        if(user.getUserAccountSeniority() < 2 && user.getUserBalance() > creditAmount*0.2){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            UserService.updateUser(user);
            return 1;
        }

        if(user.getUserAccountSeniority() >= 2 && user.getUserBalance() > creditAmount*0.1){
            user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
            UserService.updateUser(user);
            return 1;
        }

        return 0;
    }

    public int recentOut(long userId, ArrayList<Double> userMaxMonthlyOut, ArrayList<Double> monthlyBalance){
        for(int i = 0;i<userMaxMonthlyOut.size();i++){
            if(userMaxMonthlyOut.get(i) > (monthlyBalance.get(i)*0.3)){
                return 0;
            }
        }

        userEntity user = UserRepository.findByUserId(userId);
        user.setUserSavingCapacity(user.getUserSavingCapacity()+1);
        UserService.updateUser(user);
        return 1;
    }

}
