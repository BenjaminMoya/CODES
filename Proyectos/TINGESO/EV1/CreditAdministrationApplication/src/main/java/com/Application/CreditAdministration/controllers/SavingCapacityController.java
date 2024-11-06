package com.Application.CreditAdministration.controllers;

import com.Application.CreditAdministration.servicies.SavingCapacityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api/saving")
@CrossOrigin("*")
public class SavingCapacityController {

    @Autowired
    SavingCapacityService savingCapacityService;

    @PostMapping("/min")
    public int minAmount(@RequestBody Map<String, Object> body) {
        long userId = Long.parseLong(body.get("id").toString());
        double creditAmount = Double.parseDouble(body.get("amount").toString());
        return savingCapacityService.minAmount(userId, creditAmount);
    }

    @PostMapping("/history")
    public int savingHistory(@RequestBody Map<String, Object> body){
        long userId = Long.parseLong(body.get("id").toString());
        boolean greatRetirement = Boolean.parseBoolean(body.get("great").toString());
        return savingCapacityService.savingHistory(userId,greatRetirement);
    }

    @PostMapping("/periodic")
    public int periodicDeposit(@RequestBody Map<String, Object> body) {
        long userId = Long.parseLong(body.get("id").toString());
        double monthlyDeposit = Double.parseDouble(body.get("deposit").toString());
        double monthlyEntry = Double.parseDouble(body.get("entry").toString());
        boolean isPeriodic = Boolean.parseBoolean(body.get("periodic").toString());
        return savingCapacityService.periodicDeposit(userId,monthlyDeposit,monthlyEntry,isPeriodic);
    }

    @PostMapping("/relation")
    public int relationSA(@RequestBody Map<String, Object> body){
        long userId = Long.parseLong(body.get("id").toString());
        double creditAmount = Double.parseDouble(body.get("amount").toString());
        return savingCapacityService.relationSA(userId,creditAmount);
    }

    @PostMapping("/out")
    public int recentOut(@RequestBody Map<String, Object> body) {
        long userId = Long.parseLong(body.get("id").toString());
        double maxRetirement = Double.parseDouble(body.get("max").toString());
        return savingCapacityService.recentOut(userId,maxRetirement);
    }
}
