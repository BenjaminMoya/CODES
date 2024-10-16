package com.example.demo.controllers;

import com.example.demo.servicies.savingCapacityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/saving")
@CrossOrigin("*")
public class savingCapacityController {

    @Autowired
    savingCapacityService SavingCapacityService;


}
