import { Injectable } from '@nestjs/common'
import { InjectRepository } from '@nestjs/typeorm'
import { FindManyOptions, FindOneOptions, Repository } from 'typeorm'
import { User } from './entities/user.entity'
import { ApiTags } from '@nestjs/swagger'
import {CreateUserDto} from './dto/create-user.dto'

@Injectable()
@ApiTags('user')
export class UserService {
    constructor (
        @InjectRepository(User)
        private readonly userRepository: Repository<User>,
      ) {}
    
      async findAll () {
        return await this.userRepository.find()
      }

      async create (user: CreateUserDto): Promise<any> {
        try {
            const newUser = new User()
            newUser.firstName = user.firstName

            const saveUser = await this.userRepository.save(newUser)
            return saveUser
        } catch {

        }
      }
}
