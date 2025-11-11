create table greenhouse_data
(
    entry_id        int unsigned auto_increment comment '数据条目唯一ID'
        primary key,
    collect_time    datetime      not null comment '数据采集时间（格式：YYYY-MM-DD HH:MM:SS）',
    air_temp        decimal(5, 2) not null comment '空气温度（单位：℃）',
    air_humidity    decimal(5, 2) not null comment '空气相对湿度（单位：%）',
    oxygen_content  decimal(5, 2) not null comment '环境氧气含量（单位：%）',
    soil_temp       decimal(5, 2) not null comment '土壤温度（单位：℃）',
    soil_humidity   decimal(5, 2) not null comment '土壤相对湿度（单位：%）',
    light_intensity decimal(5, 2) not null comment '光照强度占比（单位：%）'
)
    comment '大棚蔬菜生长环境监测数据（存储温度、湿度、氧气、光照等实时采集数据）';

create index idx_collect_time
    on greenhouse_data (collect_time);

