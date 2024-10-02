package com.example.demo.services;

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
}
