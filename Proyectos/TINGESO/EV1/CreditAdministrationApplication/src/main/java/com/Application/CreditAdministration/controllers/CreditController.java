package com.Application.CreditAdministration.controllers;

import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.servicies.CreditService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;

@RestController
@RequestMapping("/api/credit")
@CrossOrigin("*")
public class CreditController {

    @Autowired
    CreditService creditService;

    @GetMapping("/credits/{userId}")
    public ResponseEntity<ArrayList<CreditEntity>> getUserCredits(@PathVariable long userId){
        return ResponseEntity.ok(creditService.getUserCredits(userId));
    }

    @GetMapping("/phase/{creditPhase}")
    public ResponseEntity<ArrayList<CreditEntity>> getPhaseCredits(@PathVariable int creditPhase){
        return ResponseEntity.ok(creditService.getPhaseCredits(creditPhase));
    }

    @GetMapping("/getCredit/{creditId}")
    public ResponseEntity<CreditEntity> getCredit(@PathVariable long creditId){
        return ResponseEntity.ok(creditService.getCredit(creditId));
    }

    @PostMapping("/save")
    public ResponseEntity<CreditEntity> saveCredit(@RequestBody CreditEntity credit){
        try{
            return ResponseEntity.ok(creditService.saveCredit(credit));
        } catch (Exception e) {
            return null;
        }
    }

    @PutMapping("/update")
    public ResponseEntity<CreditEntity> creditUpdate(@RequestBody CreditEntity credit){
        CreditEntity newCredit = creditService.updateCredit(credit);
        return ResponseEntity.ok(newCredit);
    }

    @GetMapping("/simulation")
    public double creditAmountSimulation(@RequestParam("amount") double requestedAmount,
                                         @RequestParam("interest") double interest,
                                         @RequestParam("years") int years){
        return creditService.creditAmountSimulation(requestedAmount,interest,years);
    }

    @GetMapping("/relation1")
    public int relationCI(@RequestParam("amount") double requestedAmount,
                          @RequestParam("interest") double interest,
                          @RequestParam("years") int years,
                          @RequestParam("entry") double monthlyEntry){
        return creditService.relationCI(requestedAmount,interest,years,monthlyEntry);
    }

    @GetMapping("/relation2")
    public int relationDI(@RequestParam("amount") double monthlyAmount,
                          @RequestParam("debts") double debtsMonthlyAmount,
                          @RequestParam("monthly") double creditMonthlyAmount){
        return creditService.relationDI(monthlyAmount,debtsMonthlyAmount,creditMonthlyAmount);
    }

    @GetMapping("/monthly")
    public double finalMonthlyAmount(@RequestParam("amount") double requestedAmount,
                                     @RequestParam("interest") double interest,
                                     @RequestParam("years") int years){
        return creditService.finalMonthlyAmount(requestedAmount,interest,years);
    }

    @GetMapping("/final")
    public double finalCreditAmount(@RequestParam("amount") double monthlyAmount,
                                    @RequestParam("years") int years,
                                    @RequestParam("requested") int requestedAmount){
        return creditService.finalCreditAmount(monthlyAmount,years,requestedAmount);
    }

    @DeleteMapping("/delete/{creditId}")
    public int deleteCredit(@PathVariable long creditId){
        try {
            return creditService.deleteCredit(creditId);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

}
