package com.example.demo.controllers;

import com.example.demo.servicies.savingCapacityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;

@RestController
@RequestMapping("/api/saving")
@CrossOrigin("*")
public class savingCapacityController {

    @Autowired
    savingCapacityService SavingCapacityService;

    @PostMapping("/min/{userId}")
    public int minAmount(@PathVariable long userId,
                         @RequestParam("amount") double creditAmount){
        return SavingCapacityService.minAmount(userId,creditAmount);
    }

    @PostMapping("/history/{userId}")
    public int savingHistory(@PathVariable long userId,
                             @RequestParam("balance") ArrayList<Double> monthlyBalance,
                             @RequestParam("max") ArrayList<Double> monthlyMaxOut){
        return SavingCapacityService.savingHistory(userId,monthlyBalance,monthlyMaxOut);
    }

    @PostMapping("/periodic/{userId}")
    public int periodicDeposit(@PathVariable long userId,
                              @RequestParam("deposit") ArrayList<Double> userDeposit,
                              @RequestParam("entry") double monthlyEntry,
                              @RequestParam("isPeriodic") boolean isPeriodic){
        return SavingCapacityService.periodicDeposit(userId,userDeposit,monthlyEntry,isPeriodic);
    }

    @PostMapping("/relation/{userId}")
    public int relationSA(@PathVariable long userId,
                          @RequestParam("amount") double creditAmount){
        return SavingCapacityService.relationSA(userId,creditAmount);
    }

    @PostMapping("/out/{userId}")
    public int recentOut(@PathVariable long userId,
                         @RequestParam("monthly") ArrayList<Double> userMaxMonthlyOut,
                         @RequestParam("balance") ArrayList<Double> monthlyBalance){
        return SavingCapacityService.recentOut(userId,userMaxMonthlyOut,monthlyBalance);
    }
}
